trait Foo1 {
    fn foo1(&self);
}

trait Foo2 {
    fn foo2(&self);
}

trait Foo3: Foo1 + Foo2 {
    fn foo3(&self);
}

fn foo4<T: Foo1 + Foo2>(i: T) {
    i.foo1();
    i.foo2();
}

struct Bar(i32);

impl Foo1 for Bar {
    fn foo1(&self) {

    }
}

impl Foo2 for Bar {
    fn foo2(&self) {

    }
}

impl Foo3 for Bar {
    fn foo3(&self) {

    }
    
}


fn main() {
}