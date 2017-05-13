module SampleText = {
  include ReactRe.Component;
  let name = "SampleText";
  type props = {value: string};
  let render {props} =>
    <ReactNative.Text style=(ReactNative.Style.(style [margin 14.]))> (ReactRe.stringToElement props.value) </ReactNative.Text>;
};

include ReactRe.CreateComponent SampleText;

let createElement ::value => wrapProps {value: value};