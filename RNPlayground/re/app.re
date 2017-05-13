module App = {
  include ReactRe.Component.JsProps;
  let name = "App";
  type props = unit;
  type jsProps = option (unit => unit);
  let jsPropsToReasonProps = Some (fun _ => ());
  let render _ => <SimpleStack test="hello"/>;
};

include ReactRe.CreateComponent App;

let createElement = wrapProps ();