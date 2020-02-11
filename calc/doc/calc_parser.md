Calculator parser
=====================

Описание грамматики
-----------------------------------

* start `expression`
* `expression` ::= `addSub`
* `addSub` ::= `mulDivMod + mulDivMod` | `mulDivMod - mulDivMod` | `mulDivMod`
* `mulDivMod` ::= `comparisons * comparisons` | `comparisons / comparisons` | `comparisons % comparisons` | `comparisons`
* `comparisons` ::= `equally >= equally` | `equally > equally` | `equally <= equally` | `equally < equally` | `equally`
* `equally` ::= `logical == logical` | `logical != logical` | `logical`
* `brackets` ::= `(addSub)` | `unary`
* `unary` ::= `- number` | `number`
* `number` ::= `number` | `digit`
* `digit` ::= `0` | `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9`
