open ReWeb;

let getUser = (user, _) =>
  user
  |> Shared.User.toString
  // For demo purposes only!
  |> Response.of_text(~headers=[("access-control-allow-origin", "*")])
  |> Lwt.return;

let server =
  fun
  | (`GET, ["bob"]) => getUser({Shared.User.id: 1, name: "Bob"})
  | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);

let () = Server.serve(server);
