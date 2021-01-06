このGitHub レポジトリはKEK PF-AR テストビームラインの電場計算を行うためのものです．

## 使い方

```shell
git clone git@github.com:t-odagawa/ElectricFieldCalculation.git
make
./calc_elec <sigma_range> <number_of_cells> <z coordinate>
```

docs/electric_field.pdf にあるような積分を考えた際に，
(x, y, z) = (5sigma_x, 0, z) での電場の積分値を近似計算します．

  - sigma_range: 電荷密度のガウス分布について +/- <sigma_range> * sigma の範囲を考える
  - number_of_cells: sigma_range * sigma をx/y/z それぞれの方向に <number_of_cells> 分割する
  - z coordinate: z 座標が <z coordinate> での電場を計算する

LSF ジョブを使う場合はshell/run_calc.sh を使うことができます．

その他，必要に応じてdocs/electric_field.pdf およびコメントを確認してください．