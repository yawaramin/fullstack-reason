// One-off binding to Fetch API

module Response = {
  type t;
  [@bs.send] external text: t => Js.Promise.t(string) = "";
};

[@bs.val] external fetch: string => Js.Promise.t(Response.t) = "";

// Helpers for the component

let setOk = (~setUser, string) =>
  Js.Promise.resolve(setUser(_ => Some(Ok(Shared.User.ofString(string)))));

let setError = (~setUser, _error) =>
  Js.Promise.resolve(setUser(_ => Some(Error("(Web request failed!)"))));

let endpoint = "http://localhost:8080/bob";

// The component

[@react.component]
let make = () => {
  let (user, setUser) = React.useState(() => None);

  React.useEffect0(() => {
    endpoint
    |> fetch
    |> Js.Promise.then_(Response.text)
    |> Js.Promise.then_(setOk(~setUser))
    |> Js.Promise.catch(setError(~setUser))
    |> ignore;

    None;
  });

  switch (user) {
  | Some(Ok({Shared.User.id, name})) =>
    <>
      <p> {React.string("ID=" ++ string_of_int(id))} </p>
      <p> {React.string("Name=" ++ name)} </p>
    </>
  | Some(Error(message)) => <p> {React.string(message)} </p>
  | None => <p> {React.string("(Loading...)")} </p>
  };
};
