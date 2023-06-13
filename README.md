# mumu-to-ZZZ
firstly, we consider these signal and backgrounds processes:
Signal: 𝝁^+ 𝝁^−→𝒁𝒁𝒁, 𝒁→𝒍^+ 𝒍^−, 𝒁→𝒍^+ 𝒍^−  , 𝒁→𝝂_𝒍 𝝂 ̃_𝒍;𝛔=𝟏.𝟎𝟐𝟔𝐞^(−𝟑) 𝐟𝐛; √𝑺=𝟏𝑻𝒆𝑽
Bkg1: 𝝁^+ 𝝁^−→𝒍^+ 𝒍^− 𝒍^+ 𝒍^−,𝛔=𝟓.𝟎𝟗𝟑𝐟𝐛;
Bkg2:𝝁^+ 𝝁^−→𝒁𝑾^+ 𝑾^−, 𝒁→𝒍^+ 𝒍^−,𝑾^+→𝒍^+ 𝝂_𝒍,𝑾^−→𝒍^− 𝝂 ̃_𝒍.𝛔=𝟕.𝟎𝟔𝟕𝐞^(−𝟑) 𝐟𝐛;
Bkg3:𝝁^+ 𝝁^−→𝝁^+ 𝝁^− 𝑾^+ 𝑾^−, 𝑾^+→𝒍^+ 𝝂_𝒍,𝑾^−→𝒍^− 𝝂 ̃_𝒍.𝛔=𝟎.𝟒𝟎𝟐𝟑𝐟𝐛;
Bkg4:𝝁^+ 𝝁^−→𝝁^+ 𝝁^− 𝒁𝒁, 𝒁→𝒍^+ 𝒍^−, 𝒁→𝝂_𝒍 𝝂 ̃_𝒍.𝛔=𝟐.𝟐𝟕𝟖𝐞^(−𝟑) 𝐟𝐛;
Bkg5:𝝁^+ 𝝁^−→𝝁^+ 𝝁^− 𝑾^+ 𝑾^− 𝐙 inclusive decay.𝛔=𝟕.𝟗𝟗𝟑𝐞^(−𝟐) 𝐟𝐛.

1.Use ntupe_chain.C to get some useful variables.
2.Use compare.C to see variables' distributions.
3.According to the distributions, do some cuts on variables(It's just an estimation).
4.use cut1.C to do optimization.
5.Finally, use cutcounting2.C to calculate significance.(Now only use s=S/sqrt(B), s is significance, S is the number of signal, and B is the number of background.).
