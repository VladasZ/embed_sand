use test_engine::rest::Req;

pub struct Network;

impl Network {
    pub const TEST: Req<(), ()> = "test".into();
}
