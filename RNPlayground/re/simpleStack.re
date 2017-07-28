open ReactNative;

open ReactNavigation;

/*type screenProps = unit;*/
type mode =
  | Editing
  | NotEditing;

/*type params = {. mode : mode, name : string};*/
let myNavScreen navigation banner::(banner: string) =>
  <ScrollView>
    <SampleText value=banner />
    <Button
      onPress=(
        Navigation.navigate
          navigation routeName::"Profile" params::{"name": "Jane", "mode": NotEditing}
      )
      title="Go to a profile screen"
    />
    <Button
      onPress=(
        Navigation.navigate
          navigation
          routeName::"Photos"
          params::(Js.Obj.assign (Navigation.state navigation).params {"mode": NotEditing})
      )
      title="Go to a photos screen"
    />
  </ScrollView>;

let myHomeScreen {StackNavigator.navigation: navigation} =>
  myNavScreen navigation banner::"Home screen";

let myPhotosScreen {StackNavigator.navigation: navigation} => {
  let name = (Navigation.state navigation).params##name;
  myNavScreen navigation banner::{j|$(name)'s Photos|j}
};

let config = None;

let routes: StackNavigator.routes int 'params =
  StackNavigator.(
    routes [
      (
        "Home",
        route
          screen::(
            fun {StackNavigator.navigation: navigation} =>
              myNavScreen navigation banner::"Home screen"
          )
          navigationOptions::(`static (navigationOptions title::"Welcome" ()))
          ()
      ),
      (
        "Photos",
        route
          screen::(
            fun {StackNavigator.navigation: navigation} => {
              let name = (Navigation.state navigation).params##name;
              myNavScreen navigation banner::{j|$(name)'s Photos|j}
            }
          )
          path::"photos/:name"
          navigationOptions::(`static (navigationOptions title::"Photos" ()))
          ()
      ),
      (
        "Profile",
        {
          /*let screen = myProfileScreen;*/
          let dynamicNavigationOptions {navigation} => {
            let state = Navigation.state navigation;
            let name = state.params##name;
            let isEditing =
              switch state.params##mode {
              | Editing => true
              | _ => false
              };
            let title = if isEditing {"Done"} else {"Edit"};
            let onPress () => {
              let mode =
                switch state.params##mode {
                | Editing => NotEditing
                | _ => Editing
                };
              Navigation.setParams navigation ((Js.Obj.assign state.params) {"mode": mode})
            };
            let headerRight = <Button title onPress />;
            navigationOptions
              headerTitle::(ReasonReact.stringToElement {j|$(name)'s Profile|j}) ::headerRight ()
          };
          route
            screen::(
              fun {StackNavigator.navigation: navigation} => {
                let (editStatus, name) = {
                  let p = (Navigation.state navigation).params;
                  let editStatus =
                    switch p##mode {
                    | Editing => "Now Editing "
                    | _ => ""
                    };
                  (editStatus, p##name)
                };
                myNavScreen navigation banner::{j|$(editStatus)$(name)'s Profile|j}
              }
            )
            path::"people/:name"
            navigationOptions::(`dynamic dynamicNavigationOptions)
            ()
        }
      )
    ]
  );

let stackRouter = StackNavigator.create routes config;

let make children => stackRouter screenProps::() children;
/*let myProfileScreen {StackNavigator.navigation: navigation} => {
    let (editStatus, name) = {
      let p = (Navigation.state navigation).params;
      let editStatus =
        switch p##mode {
        | Editing => "Now Editing "
        | _ => ""
        };
      (editStatus, p##name)
    };
    myNavScreen navigation banner::{j|$(editStatus)$(name)'s Profile|j}
  };*/
/*(
    "Photos",
    route
      screen::(
        fun {StackNavigator.navigation: navigation} => {
          let name = (Navigation.state navigation).params##name;
          myNavScreen navigation banner::{j|$(name)'s Photos|j}
        }
      )
      path::"photos/:name"
      navigationOptions::(`static (navigationOptions title::"Photos" ()))
      ()
  ),
  (
    "Profile",
    {
      /*let screen = myProfileScreen;*/
      let dynamicNavigationOptions {navigation} => {
        let state = Navigation.state navigation;
        /*
             Long / Safe way
             let name =
             switch (Js.Dict.get state.params "name") {
             | Some name => name
             | None => "Unknown"
         };*/
        /*  Yolo way */
        let name = state.params##name;
        let isEditing =
          switch state.params##mode {
          | Editing => true
          | _ => false
          };
        let title = if isEditing {"Done"} else {"Edit"};
        let onPress () => {
          let mode =
            switch state.params##mode {
            | Editing => NotEditing
            | _ => Editing
            };
          Navigation.setParams
            navigation
            (Js.Obj.assign (Js.Obj.assign (Js.Obj.empty ()) state.params) {"mode": mode})
        };
        let headerRight = <Button title onPress />;
        navigationOptions
          headerTitle::(ReasonReact.stringToElement {j|$(name)'s Profile|j})
          ::headerRight
          ()
      };
      route
        screen::(
          fun {StackNavigator.navigation: navigation} => {
            let (editStatus, name) = {
              let p = (Navigation.state navigation).params;
              let editStatus =
                switch p##mode {
                | Editing => "Now Editing "
                | _ => ""
                };
              (editStatus, p##name)
            };
            myNavScreen navigation banner::{j|$(editStatus)$(name)'s Profile|j}
          }
        )
        path::"people/:name"
        navigationOptions::(`dynamic dynamicNavigationOptions)
        ()
    }
  )*/