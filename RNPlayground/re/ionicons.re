external view : ReactRe.reactClass = "default" [@@bs.module "react-native-vector-icons/Ionicons"];

let createElement
    name::(name: string)
    size::(size: int)
    style::(style: option ReactNative.Style.t)=? =>
  ReactRe.wrapPropsShamelessly
    view {"name": name, "size": size, "style": Js.Undefined.from_opt style};