open ReWeb

type key = Key of string

module Cache = Cache.Ephemeral (struct
  type t = key

  let equal (Key k1) (Key k2) = k1 = k2

  let hash = Hashtbl.seeded_hash
end)

type topic = string Topic.t
type cache = topic Cache.t

let create cache name =
  let%lwt value = Cache.find_opt cache ~key:name in
  let%lwt topic =
    match value with
    | None ->
        Stdlib.print_endline "CREATING A TOPIC" ;
        let topic = Topic.make () in
        let%lwt () = Cache.add cache ~key:name topic in
        topic |> Lwt.return
    | Some topic ->
        Stdlib.print_endline "FOUND A TOPIC" ;
        topic |> Lwt.return
  in
  Lwt.return topic
