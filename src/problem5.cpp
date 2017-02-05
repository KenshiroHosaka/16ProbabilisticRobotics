/*
 * problem5.cpp
 * 作成者：K.hsk
 * 第8回　問題5改
 */
#include <iostream>
#include <iomanip>      //std::setw用
#include <fstream>      //ファイル入出力用
#include <vector>       //動的配列用
#include <algorithm>    //abs用

int main(){

    using std::cout;    // std::cout -> cout
    using std::endl;    // std::endl -> endl

    /// ファイル入力
    cout << "File open" << endl;
    std::fstream DATA("src/problemdata.txt");

    /// コスト，ペナルティ(ない場合はデータに0を記入)
    int COST,PENALTY;
    DATA >> COST >> PENALTY;
    cout << "COST:" << COST <<" PENALTY:" << PENALTY << endl;

    /// 各要素をファイルから読み取り後、表示
    int x_max = 0 , y_max = 0;

    DATA >> x_max >> y_max;
    std::vector<std::vector<double> > V( y_max+2 , std::vector<double>(x_max+2 , COST*10000) ); //周囲1個分確保する　全部コストよりもすごく小さい値で埋める
    std::vector<std::vector<double> > Puddle( y_max+2 , std::vector<double>(x_max+2 , 0.0) );   //水たまり用
    std::vector<std::vector<int>    > GOAL( y_max+2 , std::vector<int>(x_max+2 , 0) );          //ゴール用

    for(int i=1; i < y_max+1; i++){
        for(int j=1; j < x_max+1; j++){
            DATA >> V[i][j];
            if( 1 == V[i][j]){      //ゴール
                V[i][j] = 0.0;      //ゴールの価値は高い
                GOAL[i][j] = 1;
            }else if( 2 == V[i][j]){            //水たまり
                V[i][j] = -100.0;               //ゴール以外の価値は-10.0
                Puddle[i][j] = (double)PENALTY; //水たまりがある場所にはペナルティをおく
            }else if( 3 == V[i][j]){            //壁
                V[i][j] = COST*10000;
            }else{
                V[i][j] = -100.0;    //ゴール以外の価値は-10.0
            }
            if(V[i][j] > -1000){
                cout << std::setw(4) << V[i][j] << " ";
            }else{
                cout << "     ";
            }
        }
        cout << endl;
    }
    cout << endl << "--START--" << endl ;

    /// 各要素の価値を価値反復を用いて計算
    int count = 0;                          //ループ終了用カウント　前回と同じ値のセルが (x_max*y_max-1)と同じになったらループ終了
    std::vector<double> TEMP(4 , 0.0);
    int n=0;
    while(count != (x_max*y_max) ){
        count = 0;
        for(int i=1; i < y_max+1; i++){
            for(int j=1; j < x_max+1; j++){
                if( (GOAL[i][j] != 1) && (V[i][j] > -1000)){
                    //各方向を計算
                    TEMP[0] = V[i-1][j] + COST + Puddle[i-1][j]; //上
                    TEMP[1] = V[i][j-1] + COST + Puddle[i][j-1]; //左
                    TEMP[2] = V[i+1][j] + COST + Puddle[i+1][j]; //下
                    TEMP[3] = V[i][j+1] + COST + Puddle[i][j+1]; //右
                    //（COST*100よりも小さいのを省く）
                    for(int t=0; t<4; t++){
                        if( TEMP[t] > V[0][0] ){
                            TEMP[n] = TEMP[t];
                            n++;
                        }
                    }
                    switch(n){
                        case 2: //2方向に行ける場合
                            for(int t=0; t < n; t++){
                                TEMP[t]=0.1*TEMP[0] + 0.1*TEMP[1] + 0.8*TEMP[t];
                            }
                            break;
                        case 3: //3方向に行ける場合
                            for(int t=0; t < n; t++){
                                TEMP[t]=0.1*TEMP[0] + 0.1*TEMP[1] + 0.1*TEMP[2] + 0.7*TEMP[t];
                            }
                            break;
                        case 4: //4方向に行ける場合
                            for(int t=0; t < n; t++){
                                TEMP[t]=0.1*TEMP[0] + 0.1*TEMP[1] + 0.1*TEMP[2] + 0.1*TEMP[3] + 0.6*TEMP[t];
                            }
                            break;
                    }
                    for(int t=3; t > n-1; t--) TEMP[t] = COST*10000;

                    //上下左右で値が大きいものを残していく
                    for(int t=0; t<3 ; t++) if(TEMP[t]>TEMP[t+1]) TEMP[t+1]=TEMP[t];

                    //前回とほぼ同じ値の場合は count +1
                    if( abs(V[i][j] - TEMP[3]) <= 0.01 ) count += 1;

                    V[i][j] = TEMP[3];                              //残された一番大きい値を代入
                    cout << std::fixed << std::setprecision(1) <<std::setw(6) << V[i][j] << " " ;
                    TEMP.clear();                                   //一時計算用配列　リセット
                    n=0;

                }else if(GOAL[i][j] == 1){
                    cout << std::fixed << std::setprecision(1) <<std::setw(6) << V[i][j] << " " ;
                    count += 1;
                }else{
                    cout << "       ";
                    count += 1;
                }
            }
            cout << endl;
        }
    cout << endl;
    }
    cout << "--END--" << endl ;
    return 0;
}
