open ReWeb;

let getFile = (path, _request) =>
  path |> String.concat("/") |> Response.of_file;

let getUser = (user, _request) =>
  user
  |> Shared.User.toString
  // For demo purposes only!
  |> Response.of_text(~headers=[("access-control-allow-origin", "*")])
  |> Lwt.return;

let oneYr = 365 * 24 * 60 * 60;

let server =
  fun
  // [GET /]
  | (`GET, [""]) => getFile(["dist", "index.html"])

  /* [GET /dist/...] - caches response to any request to /dist/... for a
     year, with Webpack-hashed asset file names (i.e. revving) to bust
     cache! */
  | (`GET, ["dist", ..._] as path) =>
    Filter.cache_control(Header.CacheControl.public(~max_age=oneYr, ())) @@
    getFile(path)

  // [GET /bob]
  | (`GET, ["bob"]) => getUser({Shared.User.id: 1, name: "Bob"})
  | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);

let () = Server.serve(server);
