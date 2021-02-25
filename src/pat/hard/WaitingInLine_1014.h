//
// Created by guojm on 2021/2/20.
//

#ifndef ALGORITHM_WAITINGINLINE_1014_H
#define ALGORITHM_WAITINGINLINE_1014_H
#define LOCAL
#include <iostream>
#include <string>
#include <iomanip>

#ifdef LOCAL
#include <fstream>
#endif

using namespace std;
/**
 *
 */
namespace WaitingInLine_1014
{
    /**
     * 模拟全过程,计算每个用户的等待时间
     * 容易忽略的点：
     *      *1.注意每个新用户都要去等待队列最短的窗口
     *    ***2.到达5点时,窗口不再受理新用户，但正在接收服务的用户必须服务完！！！！
     *         所以最后输出的时间是可以超过17:00的，忽略这一点可能会导致部分错误。
     *       3. 为方便时间运算，可以从距离8:00的分钟数来计时，最后输出时再进行格式化。
     * 基本思路:
     * 用循环模拟处理过程，每个窗口用一个队列来保存等待的用户
     * 数据以分钟为单位，每次循环表示1分钟,伪代码如下
     * for(time from 0 to end_time){
     *      for(window in windows){
     *          if(window.wait_queue is empty)
     *              continue;
     *          serve_user = window.wait_queue.top;
     *          serve_user.remainder_time--;
     *          if(serve_user.remainder_time == 0){
     *              wait_queue.pop();
     *              leave_minutes[server_user] = i; //记录用户离开时间
     *              if(current_time = end_time)
     *                  wait_queue.clear();
     *          }
     *      }
     *      //扫描完窗口后向有空位的等待队列中添加新用户
     *      if(have more user && have free position && time < end_time){
     *          wait_queue = findShortestQueue();   //查找最短的队列
     *          wait_queue.push(new_user)
     *      }
     * }
     * //时间到后对于正在服务的用户仍要服务完
     * for(window in windows)
     *      serve_user = window.wait_queue.top
     *      if(serve_user != null){
     *          leave_minutes[serve_user] += server_user.remainder_time
     *      }
     * }
     * //后面直接从Leave_minutes中查询要找的用户离开时间即可
     *
     * 运行结果：AC
     */
    namespace SimpleSolution
    {
        typedef struct wait_user
        {
            int id = 0;
            wait_user* next = nullptr;
        } *wait_user_ptr;

        typedef struct
        {
            int size = 0;
            wait_user_ptr root = nullptr;
            wait_user_ptr tail = nullptr;
        }window, *window_ptr;
        //end minutes
        constexpr int END_TIME = 60 * (17 - 8);

        int N, M, K, Q;
        int* remainder_time;
        int* leave_time;
        window_ptr* windows;

        int findShortestWindow();
        void pop(int w_index);
        bool queueIsEmpty(int w_index);
        void push(int w_index,int id);
        void printTime(int minutes);
        void clear(int w_index);

        int main()
        {
            std::iostream::sync_with_stdio(false);

            cin.tie(nullptr);
#ifdef LOCAL
            // read from file for test
            fstream cin("test/WaitingInLine_1014_TestExample.txt");
#endif
            cin >> N >> M >> K >> Q;
            remainder_time = new int[K + 1];
            leave_time = new int[K + 1]();
            windows = new window_ptr[N];
            for (int i = 0; i < N; ++i) {
                windows[i] = new window();
            }
            for (int i = 0; i < K; ++i)
            {
                cin >> remainder_time[i + 1];
            }
            int current_user = 1;
            //loop run
            for (int time = 0; time <= END_TIME; time++)
            {
                bool leave = false;
                //resolve transaction
                for (int w_index = 0; w_index < N; w_index++)
                {
                    if (queueIsEmpty(w_index))
                        continue;
                    int serve_user = windows[w_index]->root->id;
                    remainder_time[serve_user]--;
                    if (remainder_time[serve_user] == 0)
                    {
                        leave = true;
                        pop(w_index);
                        leave_time[serve_user] = time;
                        //刚好时间到时清空队列.
                        if (time == END_TIME)
                            clear(w_index);
                    }
                }
                //push new user
                int line;
                while ((leave || time == 0) && current_user <= K && time < END_TIME && (line = findShortestWindow()) != -1 ){
                    push(line, current_user);
                    current_user++;
                }
            }

            for (int i = 0; i < N; ++i) {
                if (queueIsEmpty(i))
                    continue;
                int serve_user = windows[i]->root->id;
                leave_time[serve_user] = END_TIME + remainder_time[serve_user];
                remainder_time[serve_user] = 0;
            }

            int qc = 0;
            for(int i = 0; i < Q; i++) {
                cin >> qc;
                if (remainder_time[qc] == 0) {
                    printTime(leave_time[qc]);
                } else {
                    cout << "Sorry";
                }
                if (i < Q - 1) {
                    cout << "\n";
                }
            }
            return 0;
        }

        void printTime(int minutes){
            int h = minutes / 60 + 8;
            int m = minutes % 60;
            cout<<setw(2)<<setfill('0')<<h<<setw(1)<<":"<<setw(2)<<m;
        }

        inline void clear(int w_index){
            windows[w_index]->size = 0;
            windows[w_index]->root = nullptr;
            windows[w_index]->tail = nullptr;
        }

        void push(int w_index, int id)
        {
            window_ptr cw = windows[w_index];
            auto* new_wait = new wait_user{
                id,
                nullptr
            };
            if (queueIsEmpty(w_index)){
                cw->root = cw->tail = new_wait;
            } else {
                cw->tail->next = new_wait;
                cw->tail = cw->tail->next;
            }
            cw->size++;
        }

        inline bool queueIsEmpty(int w_index)
        {
            return windows[w_index]->size == 0;
        }

        void pop(int w_index)
        {
            window_ptr cw = windows[w_index];
            if (cw->size == 0)
                return;
            cw->root = cw->root->next;
            cw->size--;
        }

        /**
         * 选出队列最短且有空位的窗口，如果度满则返回-1
         * @return
         */
        int findShortestWindow()
        {
            int min_index = 0;
            for (int i = 1; i < N; i++)
            {
                if (windows[i]->size < M && windows[i]->size < windows[min_index]->size)
                {
                    min_index = i;
                }
            }
            if (windows[min_index]->size == M)
                return -1;
            return min_index;
        }
    }
};

#endif //ALGORITHM_WAITINGINLINE_1014_H
