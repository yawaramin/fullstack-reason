open ReWeb;

let getFile = (name, _request) => Response.of_file(name);

let getUser = (user, _request) =>
  user
  |> Shared.User.toString
  // For demo purposes only!
  |> Response.of_text(~headers=[("access-control-allow-origin", "*")])
  |> Lwt.return;

let server =
  fun
  // [GET /]
  | (`GET, [""]) => getFile("./build/index.html")
  // [GET /Index.js]
  | (`GET, ["Index.js"]) => getFile("./build/Index.js")
  // [GET /bob]
  | (`GET, ["bob"]) => getUser({Shared.User.id: 1, name: "Bob"})
  | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);

let () = Server.serve(server);
