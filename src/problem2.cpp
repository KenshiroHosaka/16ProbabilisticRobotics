/*
 * problem2.cpp
 * 作成者：Kenshiro.H
 * 第8回　問題2改
 */
#include <iostream>
#include <iomanip>      //std::setw用
#include <fstream>      //ファイル入出力用
#include <vector>       //動的配列用
#include <algorithm>    //std::max_element用

int main(){

    using std::cout;    // std::cout -> cout
    using std::endl;    // std::endl -> endl

    /// ファイル入力
    cout << "File open" << endl;
    std::fstream DATA("src/problem2Bdata.txt");

    /// コスト，ペナルティ(ない場合はデータに0を記入)
    int COST,PENALTY;
    DATA >> COST >> PENALTY;
    cout << "COST:" << COST <<" PENALTY:" << PENALTY << endl;

    /// 各要素をファイルから読み取り後、表示
    int x_max = 0 , y_max = 0;
    int G_i = 0, G_j = 0;   //ゴールの配列

    DATA >> x_max >> y_max;
    std::vector<std::vector<double> > V( y_max+2 , std::vector<double>(x_max+2 , COST*100) );   //周囲1個分確保する　全部コストよりもすごく小さい値で埋める
    std::vector<std::vector<double> > Puddle( y_max+2 , std::vector<double>(x_max+2 , 0.0) );    //水たまり用

    for(int i=1; i < y_max+1; i++){
        for(int j=1; j < x_max+1; j++){
            DATA >> V[i][j];
            if( 1 == V[i][j]){
                V[i][j] = 0.0;      //ゴールの価値は高い
                G_i = i;            //ゴールの場所を覚えておく
                G_j = j;
            }else if( 2 == V[i][j]){
                V[i][j] = -10.0;    //ゴール以外の価値は-10.0
                Puddle[i][j] = PENALTY; //がある場所にはペナルティをおく
            }else{
                V[i][j] = -10.0;    //ゴール以外の価値は-10.0
            }
            //cout << "[" << std::setw(4) << V[i][j] << "|" << std::setw(4) << Puddle[i][j] << "]" << " ";
            cout << std::setw(4) << V[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "--START--" << endl ;

    /// 各要素の価値を価値反復を用いて計算
    int count = 0;                          //ループ終了用カウント　前回と同じ値のセルが (x_max*y_max-1)と同じになったらループ終了
    std::vector<double> TEMP(4 , 0);
    while(count != (x_max*y_max)-1 ){
        count = 0;
        for(int i=1; i < y_max+1; i++){
            for(int j=1; j < x_max+1; j++){
                if( i != G_i || j != G_j ){
                    //cout << V[i-1][j] << "|" ;
                    TEMP[0] = V[i-1][j] + COST + Puddle[i-1][j]; //上
                    //cout << V[i][j-1] << "|" ;
                    TEMP[1] = V[i][j-1] + COST + Puddle[i][j-1]; //左
                    //cout << V[i+1][j] << "|" ;
                    TEMP[2] = V[i+1][j] + COST + Puddle[i+1][j]; //下
                    //cout << V[i][j+1] << "|" << endl;
                    TEMP[3] = V[i][j+1] + COST + Puddle[i][j+1]; //右
                    for(int t=0; t<3 ; t++){
                        if(TEMP[t]>TEMP[t+1]) TEMP[t+1]=TEMP[t];    //上下左右で値が大きいものを残していく
                    }
                    if(V[i][j] == TEMP[3]) count += 1;              //前回と同じ値の場合は count +1
                    V[i][j] = TEMP[3];                              //残された一番大きい値を代入
                    TEMP.clear();                                   //一時計算用配列　リセット
                }
                cout << std::setw(4) << V[i][j] << " " ;
            }
            cout << endl;
        }
    cout << endl;
    }
    cout << "--END--" << endl ;
    return 0;
}
