/**----------------------------------------------------------*
 * first version: 2024/12/19                                 *
 * github: https://github.com/sanoesogood                    *                              
 *----------------------------------------------------------**/

#include <stdio.h>
#include <math.h>

/**
 * method 1: 不分段暴力求解
 * 
 * 計算方法請看 method 2
 */
int main(){
    float x = 0, 
          y = 0;
    float x_i = -5,  
          x_f = 5,
          dx = 0.001;
    float area = 0;

    x = x_i;
    while(x <= x_f){
        y = sqrt(225 - 9*x*x);
        if(y >= sqrt(100 - x*x)){
            y = sqrt(100 - x*x);
        }

        area += y * dx;
        x += dx;
    }

    printf("area = %f", 2 * area);
    return 0;
}




/**
 * method 2: 分段求解
 * 
 * equation:
 *   ellipse : (x/5)^2 + (y/15)^2 = 1 => y = +sqrt(225 - 9*x*x) or -sqrt(225 - 9*x*x)
 *   circle  : x^2 + y^2 = 100 => y = +sqrt(100 - x*x) or -sqrt(100 - x*x)
 * 
 * intersection points: 
 *   x                |   y
 *   -----------------|-----------------
 *   -5*sqrt(10) / 4  |  -15*sqrt(6) / 4
 *   -----------------|-----------------
 *   -5*sqrt(10) / 4  |  15*sqrt(6) / 4
 *   -----------------|-----------------
 *   5*sqrt(10) / 4   |  -15*sqrt(6) / 4
 *   -----------------|-----------------
 *   5*sqrt(10) / 4   |  15*sqrt(6) / 4
 * 
 * 為了計算橢圓和圓交集的面積，先建立一個分段函數 F(x)
 *   F(x) : sqrt(225 - 9*x*x) if -5 <= x < -5*sqrt(10) / 4
 *        : sqrt(100 - x*x)   if -5*sqrt(10) / 4 <= x < 5*sqrt(10) / 4
 *        : sqrt(225 - 9*x*x) if 5*sqrt(10) / 4 <= x <= 5
 * 
 * 因為函數對稱 x 軸，所以此處只考慮橢圓和圓上半部
 * 
 * 根據微積分的概念，給定一小量 dx (底邊) 乘以函數值 F(x) (高)，得到一小塊的矩形面積 F(x)dx；將所有的矩形面積加起來即可得到 F(x) 與 x 軸圍成的面積的近似值
 * 最後再乘以 2 就是 (x/5)^2 + (y/15)^2 <= 1 與 x^2 + y^2 <= 100 之交集面積。
 */
// int main(){
//     float x = 0, 
//           y = 0;
//     float x_i = -5,  
//           x_f = 5,
//           dx = 0.001;
//     float area = 0;
    
//     x = x_i;
//     while(x < -5*sqrt(10) / 4){
//         area += sqrt(225 - 9*x*x) * dx;
//         x += dx;
//     }

//     while(x < 5*sqrt(10) / 4){
//         area += sqrt(100 - x*x) * dx;
//         x += dx;
//     }

//     while(x <= x_f){
//         area += sqrt(225 - 9*x*x) * dx;
//         x += dx;
//     }

//     printf("area = %f", 2 * area);
//     return 0;
// }
