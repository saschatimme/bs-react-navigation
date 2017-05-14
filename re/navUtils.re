let option_map fn opt_value =>
  switch opt_value {
  | None => None
  | Some value => Some (fn value)
  };

/* Until upstreamed to bs */
let dictFromList entries => {
  let dict = Js.Dict.empty ();
  let rec loop =
    fun
    | [] => dict
    | [(key, value), ...rest] => {
        Js.Dict.set dict key value;
        loop rest
      };
  loop entries
};


type value;

external value : 'a => value = "%identity";

let setValue dict key x =>
  switch x {
  | Some y =>
    let val_ = value y;
    Js.Dict.set dict key val_
  | None => ()
  };