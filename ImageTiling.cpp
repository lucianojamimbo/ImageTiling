#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include<string>


int main()
{
    
    int tilesize = 0;
    std::cout << "define tilesize" << std::endl;
    std::cin >> tilesize;

    cv::Mat img;
    cv::Mat dst;
    int x = 0;
    int y = 0;
    int widthtoadd = 0;
    int heighttoadd = 0;
    int borderType = cv::BORDER_REFLECT;

    std::vector<cv::String> fn;
    cv::glob("Data/*.*", fn, false);
    size_t count = fn.size(); //number of png files in images folder
    std::cout << fn.size() << " images found" << std::endl;


    for (int i = 0; i < fn.size(); i++){

        img = cv::imread(fn[i]);

        std::cout << "processing image: " << i << std::endl;

        heighttoadd = 0;
        if (img.size().height % tilesize != 0) {
            if ((img.size().height % tilesize) > (tilesize / 2)) {
                heighttoadd = tilesize % (img.size().height % tilesize);
            }
            else {
                heighttoadd = tilesize - (img.size().height % tilesize);
            }
        };

        widthtoadd = 0;
        if (img.size().width % tilesize != 0) {
            if ((img.size().width % tilesize) > (tilesize / 2)) {
                widthtoadd = tilesize % (img.size().width % tilesize);
            }
            else {
                widthtoadd = tilesize - (img.size().width % tilesize);
            }
        };

        cv::copyMakeBorder(img, dst, 0, heighttoadd, 0, widthtoadd, borderType, (0, 0, 0));
    
        x = 0;
        y = 0;

        for (int tiles = 0; tiles < 1 + ((dst.size().width / tilesize) * (dst.size().height / tilesize)); tiles++) {

            cv::Rect region_of_interest = cv::Rect(x, y, tilesize, tilesize);
            cv::Mat image_roi = dst(region_of_interest);

            cv::imwrite("Outputs/" + std::to_string(i) + "_" + std::to_string(tiles) + ".png" , image_roi);

            if (x + tilesize < dst.size().width) {
                x += tilesize;
            }
            else if (y + tilesize < dst.size().height) {
                y += tilesize;
                x = 0;
            }

        }

    }

    return 0;
}
