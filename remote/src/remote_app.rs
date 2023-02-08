use std::{
    path::PathBuf,
    sync::{mpsc::channel, Arc},
};

use test_engine::{
    gm::flat::Size,
    paths::home,
    rest::{raw_request, Method, API},
    rtools::init_log,
    ui::{refs::Own, View},
    App, AppCore,
};
use tokio::{spawn, sync::Mutex};

use crate::main_view::MainView;

pub struct RemoteApp {
    core: AppCore,
}

impl App for RemoteApp {
    fn setup()
    where Self: Sized {
        init_log(false, 4);

        let (send, recv) = channel::<String>();

        let send = Arc::new(Mutex::new(send));

        spawn(async move {
            for i in 0..255 {
                let send = send.clone();
                spawn(async move {
                    let ip = format!("192.168.10.{i}");

                    let res =
                        raw_request(Method::Get, format!("http://{ip}/identify_remote_board"), None).await;
                    if let Ok(res) = res {
                        if res.is_ok() && res.body == "OK" {
                            send.lock().await.send(ip).unwrap();
                        }
                    }
                });
            }
        });

        let ip: String;

        loop {
            match recv.recv() {
                Err(_) => (),
                Ok(r_ip) => {
                    ip = r_ip;
                    break;
                }
            };
        }

        API::init(API::new(ip));
    }

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
