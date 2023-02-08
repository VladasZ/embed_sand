#![allow(incomplete_features)]
#![feature(const_trait_impl)]
#![feature(const_convert)]
#![feature(specialization)]
#![feature(arbitrary_self_types)]

mod main_view;
mod network;
mod remote_app;

use test_engine::{App, MakeApp};

use crate::remote_app::RemoteApp;

#[tokio::main]
async fn main() {
    RemoteApp::make_app().launch();
}
