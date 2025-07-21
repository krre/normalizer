use std::rc::Rc;

use antiq::Application;
use antiq::Context;

pub struct Normalizer {
    _context: Rc<Context>,
}

impl Application for Normalizer {
    fn new(context: Rc<Context>) -> Self {
        Self { _context: context }
    }

    fn run(&self) {
        antiq::log("Run Webassembly Normalizer");
    }
}
