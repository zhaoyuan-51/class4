#include <fmt/format.h>

#include <opencv2/opencv.hpp>

#include "include/armor.hpp"
#include "include/img_tools.hpp"
#include "tasks/detector.hpp"
#include "tasks/plotter.hpp"

using namespace auto_aim;

int main()
{
  Detector detector;
  Plotter plotter;

  std::list<Armor> armors;
  cv::VideoCapture video(0, cv::CAP_V4L2);

  while (true) {
    cv::Mat bgr_img;
    video.read(bgr_img);  // 从视频读取一帧

    armors = detector.detect(bgr_img);
    nlohmann::json data;
    data["armor_x"] = armors.front().center.x;
    data["armor_y"] = armors.front().center.y;

    plotter.plot(data);
    // 显示装甲板，调试用
    cv::Mat draw_armor = bgr_img.clone();

    for (const auto & armor : armors) {
      // 熟悉的绘图函数
      tools::draw_points(draw_armor, armor.points);
      tools::draw_text(
        draw_armor,
        fmt::format("{},{}:{:.2f}", COLORS[armor.color], ARMOR_NAMES[armor.name], armor.confidence),
        armor.left.top);
    }

    cv::imshow("draw_armor", draw_armor);
    auto key = cv::waitKey(25);  // 阻塞 25 ms
    if (key == 'q') break;       // 按下 q 后退出
  }

  return 0;
}