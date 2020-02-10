open ReWeb;

let timeout = 0.25;

let socket = (topic, _) => {
  let%lwt subscription = Topic.subscribe(topic);

  let rec handler = (pull, push) => {
    let incoming = pull(timeout);
    let outgoing = Topic.pull(subscription, ~timeout);
    let%lwt incoming = incoming;
    let%lwt outgoing = outgoing;

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
