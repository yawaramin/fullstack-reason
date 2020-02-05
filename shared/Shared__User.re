[@deriving to_yojson]
[@decco.decode]
type t = {
  id: int,
  name: string,
};

/** [toString(user)] is a string representation of the user. */
let toString = ({id, name}) => {j|ID=$id, name=$name|j};
