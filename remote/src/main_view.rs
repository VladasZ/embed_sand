use ui::{refs::Weak, view, SubView, ViewSetup};
use ui_views::{async_link_button, Button};

use crate::network::Network;

#[view]
#[derive(Default)]
pub struct MainView {
    test: SubView<Button>,
}

impl MainView {
    async fn test_tapped(self: Weak<Self>) {
        let res = Network::TEST.get().await;
        dbg!(&res);
    }
}

impl ViewSetup for MainView {
    fn setup(mut self: Weak<Self>) {
        self.test.place.size(100, 100).center();
        self.test.set_text("Test");
        async_link_button!(self, test, test_tapped);
    }
}
