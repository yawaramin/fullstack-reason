open ReWeb;

let getFile = (path, _request) =>
  path |> String.concat("/") |> Response.of_file;

let timeout = 0.25;

let socket = (cache, name, _) => {
  let%lwt topic = Context.create(cache, Context.Key(name));
  let%lwt subscription = Topic.subscribe(topic);

  let rec handler = (pull, push) => {
    let incoming = pull(timeout);
    let outgoing = Topic.pull(subscription, ~timeout);
    let%lwt incoming = incoming;
    let%lwt outgoing = outgoing;
    let incoming = switch incoming {
    	| Ok(message) => Some(message)
    	| Error(_) => None
		};

    Option.iter(push, outgoing);
    let%lwt () =
      Option.fold(
        ~none=Lwt.return_unit,
        ~some=msg => Topic.publish(topic, ~msg),
        incoming,
      );
    handler(pull, push);
  };

  handler |> Response.of_websocket |> Lwt.return;
};

let max_age = 30 * 24 * 60 * 60;

let cache: Context.cache = Context.Cache.make();

let server =
  fun
  // [GET /]
  | (`GET, [""]) => getFile(["dist", "index.html"])

  // [GET /ws]
  | (`GET, ["ws", _name]) => socket(cache, "FOO")

  /* [GET /dist/...] - caches response to any request to /dist/... for a
     month, with Webpack-hashed asset file names (i.e. revving) to bust
     cache! */
  | (`GET, ["dist", ..._] as path) =>
    Filter.cache_control(Header.CacheControl.public(~max_age, ())) @@
    getFile(path)

  | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);

let () = Server.serve(server);
