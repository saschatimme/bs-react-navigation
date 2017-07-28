let component = ReasonReact.statelessComponent "App";

let make _children => {...component, render: fun _ => <AppNavigator />};

let jsComponent = ReasonReact.wrapReasonForJs ::component (fun _ => make [||]);