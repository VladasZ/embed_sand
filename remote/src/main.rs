use std::path::PathBuf;

use test_engine::{
    gm::flat::Size,
    paths::home,
    ui,
    ui::{refs::Own, View},
    view, App, AppCore, MakeApp,
};

#[view]
#[derive(Default)]
struct MainView {}

struct RemoteApp {
    core: AppCore,
}

impl App for RemoteApp {
    fn screen_size() -> Size
    where Self: Sized {
        (1000, 1000).into()
    }

    fn assets_path() -> PathBuf
    where Self: Sized {
        home().join("remote/remote/deps/test_engine")
    }

    fn make_root_view() -> Own<dyn View>
    where Self: Sized {
        Own::<MainView>::default()
    }

    fn with_core(core: AppCore) -> Self
    where Self: Sized {
        Self { core }
    }

    fn core(&mut self) -> &mut AppCore {
        &mut self.core
    }
}

#[tokio::main]
async fn main() {
    RemoteApp::make_app().launch();
}
