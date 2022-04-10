/**
 * 这段程序有问题，看起来非常正确的程序无法通过编译
 * 因为 TimeKeeper time_keeper(Timer()); 被解析成了函数说明而不是定义一个TimeKeeper对象
 * 确实是最令人费解的解析
 */
class Timer {
 public:
  Timer();
};

class TimeKeeper {
 public:
  TimeKeeper(const Timer& t);

  int get_time();
};

int main() {
  TimeKeeper time_keeper(Timer());
  return time_keeper.get_time();
}