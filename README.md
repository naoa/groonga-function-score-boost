# score_boost Groonga function

* ``score_boost(float)``

scoreをブーストするセレクター関数。

関数が呼ばれたタイミングでスコアブーストする。optimizerによって、順番がいじられる可能性はある。


## Install

Install libgroonga-dev.

Build this function.

    % sh autogen.sh
    % ./configure
    % make
    % sudo make install

## Usage

Register `functions/score_boost`:

    % groonga DB
    > register functions/score_boost

## License

Public domain. You can copy and modify this project freely.
