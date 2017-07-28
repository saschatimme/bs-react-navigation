external reactClass : ReasonReact.reactClass =
  "default" [@@bs.module "react-native-vector-icons/Ionicons"];

let make
    name::(name: string)
    size::(size: int)
    style::(style: option ReactNative.Style.t)=?
    children =>
  ReasonReact.wrapJsForReason
    ::reactClass
    props::{"name": name, "size": size, "style": Js.Undefined.from_opt style}
    children;