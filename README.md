#2016年度　確率ロボティクス課題
　このリポジトリは，確率ロボティクスの課題用のリポジトリである．

##第8回スライド問題回答
　アルゴリズムの確認，プログラム作成などの練習の意味も兼ねて，第8回講義の問題を解いた．解いた結果はTravisCIで表示する.  
各問題のグラフの環境は，src内の~data.txtから与えられる.  
---「~data.txt」内の意味---  
`-1 -100`     //一つ目の数字は各移動にかかるコスト，二つ目の数字は水たまりのペナルティ(ない場合は0を記入).  
`3 4`          //一つ目の数字はグラフの横の数，二つ目の数字はグラフの縦の数  
`3 3 1`       //グラフ左上から順番に並んでる　各数字の意味:0:何もない  
`0 0 0`       //各数字の意味:1:ゴール  
`0 2 0`       //各数字の意味:2:水たまり  
`0 0 0`       //各数字の意味:3:立ち入り禁止エリア  


1.　問題1  
https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198312556  
2.　問題2  
R=1 :https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198453786  
R=10:https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198454162  
3.　問題3    
https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198454655  
4.　問題4  
R=1   :https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198455028  
R=10  :https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198455276  
R=100 :https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198455434  
5.　問題5  
https://travis-ci.org/KenshiroHosaka/16ProbabilisticRobotics/builds/198455935  

##発展課題  
　発展課題として以下のグラフの有限MDP問題を解く.  

+ 移動にかかるコストは「-1」
+ 水たまりに入るときのコストは「-100」
+ 第8回スライド中の問題3と同様の遷移条件  
  　
　グラフはこれ↓
 
