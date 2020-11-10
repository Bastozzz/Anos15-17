globals[breedin minemax planesmax kamimax solmax genmax flagsmax tanksmax capturasa capturasb prob ponto baseAx baseAy baseBx baseBy atual given paint]
extensions[sound]

breed[soldados soldado]
breed[generais general]
breed[bandeiras bandeira]
breed[kits kit]
breed[tanks tank]
breed[planes plane]
breed[kamikazes kamikaze]
breed[minas mina]
turtles-own[exercito nrg]
soldados-own[vitorias]

to setup
  clear-output
  reset-ticks
  clear-all-plots
  clear-turtles
  file-close
  set capturasa 0
  set capturasb 0
  set baseAx min-pxcor
  set baseAy min-pycor
  set baseBx max-pxcor
  set baseBy max-pycor
  setup-patches
  setup-turtles
end

to setup-patches
  clear-patches
  ask patches
  [
    set pcolor green
  ]
  setup-baseA
  setup-baseB
end

to setup-baseA
  while[baseAx <= min-pxcor + lado]
  [
    set baseAy min-pycor
    while[baseAy <= min-pycor + lado]
    [
      ask patch baseAx baseAy
      [
        set pcolor red
      ]
      set baseAy baseAy + 1
    ]
    set baseAx baseAx + 1
  ]
end

to setup-baseB
  while[baseBx >= max-pxcor - lado]
  [
    set baseBy max-pycor
    while[baseBy >= max-pycor - lado]
    [
      ask patch baseBx baseBy
      [
        set pcolor turquoise
      ]
      set baseBy baseBy - 1
    ]
    set baseBx baseBx - 1
  ]
end

to setup-turtles
  create-soldados soldadosA
  [
    set vitorias 0
    set nrg energia
    set exercito "A"
    set color red
    set heading one-of [0 90 180 270]
    set shape "person soldier"
    setxy random-xcor random-ycor
    while[[pcolor] of patch-here != red]
    [
      setxy random-xcor random-ycor
    ]
  ]
  create-soldados soldadosB
  [
    set vitorias 0
    set nrg energia
    set exercito "B"
    set color turquoise
    set heading one-of [0 90 180 270]
    set shape "person soldier"
    setxy random-xcor random-ycor
    while[[pcolor] of patch-here != turquoise]
    [
      setxy random-xcor random-ycor
    ]
  ]
  create-generais generaisA
  [
    set nrg energia
    set exercito "A"
    set color red
    set heading one-of [0 90 180 270]
    set size 1.3
    set shape "person police"
    setxy random-xcor random-ycor
    while[[pcolor] of patch-here != red]
    [
      setxy random-xcor random-ycor
    ]
  ]
  create-generais generaisB
  [
    set nrg energia
    set exercito "B"
    set color turquoise
    set heading one-of [0 90 180 270]
    set shape "person police"
    set size 1.3
    setxy random-xcor random-ycor
    while[[pcolor] of patch-here != turquoise]
    [
      setxy random-xcor random-ycor
    ]
  ]
  if flag
  [
    create-bandeiras flags
    [
      set nrg 1
      set shape "flag"
      set color blue
      set size 2
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != green]
      [
        setxy random-xcor random-ycor
      ]
    ]
  ]
  if tanks?
  [
    create-tanks tanksA
    [
      set nrg energia * 1.5
      set exercito "A"
      set size 2
      set shape "tank"
      set heading one-of [0 90 180 270]
      set color red
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != red]
      [
        setxy random-xcor random-ycor
      ]
    ]
    create-tanks tanksB
    [
      set nrg energia * 1.5
      set exercito "B"
      set size 2
      set shape "tank"
      set heading one-of [0 90 180 270]
      set color turquoise
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != turquoise]
      [
        setxy random-xcor random-ycor
      ]
    ]
  ]
  if kamikaze?
  [
    create-kamikazes kamikazeA
    [
      set label "K"
      set nrg energia
      set exercito "A"
      set color red
      set heading one-of [0 90 180 270]
      set shape "person soldier"
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != red]
      [
        setxy random-xcor random-ycor
      ]
    ]
    create-kamikazes kamikazeB
    [
      set nrg energia
      set exercito "B"
      set color turquoise
      set heading one-of [0 90 180 270]
      set shape "person soldier"
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != turquoise]
      [
        setxy random-xcor random-ycor
      ]
    ]
  ]
  if planes?
  [
    create-planes planesA
    [
      set nrg energia * 1.5
      set exercito "A"
      set size 3.5
      set shape "airplane 2"
      set heading one-of [0 90 180 270]
      set color red
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != red]
      [
        setxy random-xcor random-ycor
        if count (planes-on patch-here) != 1
        [
          setxy random-xcor random-ycor
        ]
      ]
    ]
    create-planes planesB
    [
      set nrg energia * 1.5
      set exercito "B"
      set size 3.5
      set shape "airplane 2"
      set heading one-of [0 90 180 270]
      set color turquoise
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != turquoise]
      [
        setxy random-xcor random-ycor
        if count (planes-on patch-here) != 1
        [
          setxy random-xcor random-ycor
        ]
      ]
    ]
  ]
  if mines?
  [
    create-minas mines
    [
      set nrg 1
      set shape "mine"
      set heading 0
      setxy random-xcor random-ycor
      while[[pcolor] of patch-here != green]
      [
        setxy random-xcor random-ycor
      ]
    ]
  ]
end

to start
  if ticks = 1
  [
    sound:play-sound "warsounds.mp3"
  ]
  set breedin soldados
  move-soldados
  if kamikaze?
  [
    set breedin kamikazes
    move-soldados
  ]
  move-generais
  if tanks?
  [
    move-tanks
  ]
  if medkits
  [
    spawn-kits
  ]
  if planes?
  [
    move-planes
  ]
  check-kits
  check-flag
  check-nrg
  tick
  if not any? turtles with[breed != bandeiras and breed != kits and breed != kits] or (not any? patches with [pcolor = red] or not any? patches with [pcolor = turquoise] and not any? patches with [pcolor = green])
  [
    ifelse count patches with [pcolor = red] > count patches with [pcolor = turquoise]
    [
      output-type "RED ARMY WINS!!!"
      victory-song
    ]
    [
      ifelse count patches with [pcolor = red] < count patches with [pcolor = turquoise]
      [
        output-type "TURQUOISE ARMY WINS!!!"
        victory-song
      ]
      [
        output-type "IT'S A DRAW!!!"
      ]
    ]
    stop
  ]
end

to victory-song
  sound:play-note "Marimba" 60 64 0.25
  sound:play-note-later 0.2 "Marimba" 60 64 0.15
  sound:play-note-later 0.3 "Marimba" 60 64 0.15
  sound:play-note-later 0.4 "Marimba" 67 64 2

  sound:play-note "Trumpet" 60 64 0.25
  sound:play-note-later 0.2 "Trumpet" 60 64 0.15
  sound:play-note-later 0.3 "Trumpet" 60 64 0.15
  sound:play-note-later 0.4 "Trumpet" 67 64 2
end

to check-nrg
  ask kamikazes
  [
    if nrg <= 0
    [
      let val one-of[2 3 4 5]
      ask patches in-radius val
      [
        set pcolor 32
        sound:play-drum "Bass Drum 1" 100
      ]
      ask turtles in-radius val with[breed != tanks and breed != planes]
      [
        set nrg 0
      ]
      ask tanks in-radius val
      [
        set nrg nrg - (energia / 2)
      ]
      die
    ]
  ]
  ask turtles with [breed != tanks and breed != kamikazes]
  [
    if nrg <= 0
    [
      die
    ]
  ]
end

to spawn-kits
  if (remainder ticks intervalo) = 0
  [
    create-kits 1
    [
      set nrg regen
      set shape "medkit"
      set color white
      set size 1.2
      set heading 0
      setxy random-xcor random-ycor
    ]
    sound:play-sound "med.wav"
  ]
end

to move-planes
  ask planes
  [
    set paint color
    ifelse any? planes-on patch-ahead 2
    [
      ifelse random 101 <= 50
      [
        right 45
        fd 1
        set nrg nrg - 1
      ]
      [
        left 45
        fd 1
        set nrg nrg - 1
      ]
    ]
    [
      ifelse random 101 <= 95
      [
        fd 1
        set nrg nrg - 1
      ]
      [
        ifelse random 101 <= 50
        [
          left 45
          fd 1
          set nrg nrg - 1
        ]
        [
          right 45
          fd 1
          set nrg nrg - 1
        ]
      ]
    ]
    if remainder ticks 5 = 0
    [
      ask patches in-radius one-of [4 5 6 7]
      [
        set pcolor paint
      ]
    ]
    if count planes-on patch-here > 1
    [
      ask patches in-radius one-of [4 5 6 7]
      [
        set pcolor 32
        sound:play-drum "Bass Drum 1" 100
      ]
      ask turtles in-radius one-of [4 5 6 7]
      [
        set nrg 0
      ]
    ]
  ]

end

to move-tanks
  ask tanks
  [
    set atual exercito
    set paint color
    if nrg <= 0
    [
      hatch-generais 3
      [
        set nrg 500
        set exercito atual
        set color paint
        set heading one-of [0 90 180 270]
        set size 1.3
        set shape "person police"
        setxy xcor ycor
      ]
      hatch-soldados 3
      [
        set nrg 500
        set exercito atual
        set color paint
        set size 1
        set heading one-of [0 90 180 270]
        set shape "person soldier"
        setxy xcor ycor
      ]
      die
    ]
    ifelse any? (turtles-on neighbors) with [exercito != atual and breed != bandeiras and breed != kits and breed != tanks and breed != planes]
    [
      ask (turtles-on neighbors) with [exercito != atual and breed != bandeiras and breed != kits and breed != tanks and breed != planes]
      [
        set prob 101
        batalhas
      ]
      set nrg nrg - 10
    ]
    [
      ifelse any? (tanks-on neighbors) with [exercito != atual]
      [
        ask (tanks-on neighbors) with [exercito != atual]
        [
          if [xcor] of self > [xcor] of myself[set ponto "Direita"]
          if [xcor] of self < [xcor] of myself[set ponto "Esquerda"]
          if [ycor] of self < [xcor] of myself[set ponto "Tras"]
        ]
        if ponto = "Direita"[right 90]
        if ponto = "Esquerda"[left 90]
        if ponto = "Tras"[right 180]
        set prob 50
        batalhas
        fd  -3
        right 90
      ]
      [
        ifelse [pcolor] of patch-ahead 2 != paint and remainder ticks 3 = 0
        [
          fd 1
          ask neighbors
          [
            set pcolor paint
          ]
          set nrg nrg - 2
        ]
        [
          ifelse [pcolor] of patch-right-and-ahead 90 2 != paint and remainder ticks 3 = 0
          [
            right 90
            fd 1
            ask neighbors
            [
              set pcolor paint
            ]
            set nrg nrg - 2
          ]
          [
            ifelse [pcolor] of patch-left-and-ahead 90 2 != paint and remainder ticks 3 = 0
            [
              left 90
              fd 1
              ask neighbors
              [
                set pcolor paint
              ]
              set nrg nrg - 2
            ]
            [
              ifelse [pcolor] of patch-right-and-ahead 180 2 != paint and remainder ticks 3 = 0
              [
                right 90
                fd 1
                ask neighbors
                [
                  set pcolor paint
                ]
                set nrg nrg - 2
              ]
              [
                ifelse mov_alternativo
                [
                  ifelse random 101 <= 90 and remainder ticks 3 = 0
                  [
                    fd 1
                    ask neighbors
                    [
                      set pcolor paint
                    ]
                    set nrg nrg - 2
                  ]
                  [
                    ifelse random 101 <= 50 and remainder ticks 3 = 0
                    [
                      right 90
                      fd 1
                      ask neighbors
                      [
                        set pcolor paint
                      ]
                      set nrg nrg - 2
                    ]
                    [
                      ifelse random 101 <= 50 and remainder ticks 3 = 0
                      [
                        left 90
                        fd 1
                        ask neighbors
                        [
                          set pcolor paint
                        ]
                        set nrg nrg - 2
                      ]
                      [
                        ifelse remainder ticks 3 = 0
                        [
                          right 180
                          fd 1
                          ask neighbors
                          [
                            set pcolor paint
                          ]
                          set nrg nrg - 2
                        ]
                        [
                          set nrg nrg - 1
                        ]
                      ]
                    ]
                  ]
                ]
                [
                  fd 1
                  ask neighbors
                  [
                    set pcolor paint
                  ]
                  set nrg nrg - 2
                ]
              ]
            ]
          ]
        ]
      ]
    ]
  ]
end

to check-kits
  ask kits
  [
    if any? (turtles-on patch-here) with [breed != flags and breed != kits and breed != tanks and breed != planes]
    [
      let unit (turtles-on patch-here)
      ask unit
      [
        set nrg nrg + regen
      ]
      die
    ]
  ]
end

to batalhas
  ifelse random 101 <= prob
  [
    set nrg nrg / 2
    set nrg nrg - 1
  ]
  [
    let loser (turtles-on patch-ahead 1) with [exercito != atual and breed != planes]
    ask loser
    [
      set given nrg / 2
    ]
    set nrg nrg + given
    set nrg nrg - 1
    if breed = soldados
    [
      set vitorias vitorias + 1
    ]
    if mov_alternativo
    [
      fd -1
    ]
  ]
end

to move-soldados
  ask breedin
  [
    set paint color
    set atual exercito
    ifelse any? (soldados-on patch-ahead 1) with [exercito != atual] and any? (soldados-on patch-right-and-ahead 90 1) with [exercito != atual]
    [
      if random 101 <= 50
      [
        right 90
      ]
      if nrg < energia
      [
        set nrg nrg / 2
      ]
      set prob 50
      batalhas
    ]
    [
      ifelse any? (soldados-on patch-ahead 1) with [exercito != atual]
      [
        if nrg < energia
        [
          set nrg nrg / 2
        ]
        set prob 50
        batalhas
      ]
      [
        ifelse any? (soldados-on patch-right-and-ahead 90 1) with [exercito != atual]
        [
          right 90
          if nrg < energia
          [
            set nrg nrg / 2
          ]
          set prob 50
          batalhas
        ]
        [
          ifelse any? (generais-on patch-right-and-ahead 90 1) with [exercito != atual] or any? (generais-on patch-ahead 1) with [exercito != atual]
          [
            fd -2
            set nrg nrg - 1
          ]
          [
            ifelse any? (generais-on patch-right-and-ahead 90 1) with [exercito != atual] and any? (generais-on patch-ahead 1) with [exercito != atual]
            [
              if random 101 <= 50
              [
                right 90
              ]
              if nrg < energia
              [
                set nrg nrg / 2
              ]
              set prob 75
              batalhas
            ]
            [
              ifelse any? (tanks-on patch-right-and-ahead 90 1) with [exercito != atual] and any? (tanks-on patch-ahead 1) with [exercito != atual]
              [
                fd -2
                set nrg nrg - 1
              ]
              [
                ifelse [pcolor] of patch-ahead 1 != paint
                [
                  fd 1
                  ask patch-here
                  [
                    set pcolor paint
                  ]
                  set nrg nrg - 2
                ]
                [
                  ifelse [pcolor] of patch-right-and-ahead 90 1 != paint
                  [
                    right 90
                    fd 1
                    ask patch-here
                    [
                      set pcolor paint
                    ]
                    set nrg nrg - 2
                  ]
                  [
                    ifelse flag
                    [
                      ifelse any? bandeiras-on patch-ahead 1
                      [
                        fd 1
                        set nrg nrg - 1
                      ]
                      [
                        ifelse any? bandeiras-on patch-right-and-ahead 90 1
                        [
                          right 90
                          fd 1
                          set nrg nrg - 1
                        ]
                        [
                          ifelse random 101 <= 90
                          [
                            fd 1
                            set nrg nrg - 1
                          ]
                          [
                            right 90
                            fd 1
                            set nrg nrg - 1
                          ]
                        ]
                      ]
                    ]
                    [
                      ifelse mov_alternativo
                      [
                        ifelse random 101 <= 90
                        [
                          fd 1
                          set nrg nrg - 1
                        ]
                        [
                          right 90
                          fd 1
                          set nrg nrg - 1
                        ]
                      ]
                      [
                        fd 1
                        set nrg nrg - 1
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]
  ]
end



to move-generais
  ask generais
  [
    set paint color
    set atual exercito
    if any? (soldados-on neighbors4) with [exercito = atual] and not tanks?
    [
      let i count (soldados-on neighbors4) with [exercito = atual]
      while [i > 0]
      [
        set nrg nrg * 1.05
        set i i - 1
      ]
    ]
    ifelse count (turtles-on neighbors4) with [exercito != atual and breed != bandeiras and breed != kits and breed != planes] = 1 and any? (generais-on neighbors4) with [exercito != atual]
    [
      ask (generais-on neighbors4)
      [
        if [xcor] of self > [xcor] of myself[set ponto "Direita"]
        if [xcor] of self < [xcor] of myself[set ponto "Esquerda"]
        if [ycor] of self < [xcor] of myself[set ponto "Tras"]
      ]
      if ponto = "Direita"[right 90]
      if ponto = "Esquerda"[left 90]
      if ponto = "Tras"[right 180]
      set prob 50
      batalhas
    ]
    [
      ifelse count (turtles-on neighbors4) with [exercito != atual  and breed != bandeiras and breed != kits and breed != planes] = 1 and any? (soldados-on neighbors4) with [exercito != atual]
      [
        ask (soldados-on neighbors4)
        [
          if [xcor] of self > [xcor] of myself[set ponto "Direita"]
          if [xcor] of self < [xcor] of myself[set ponto "Esquerda"]
          if [ycor] of self < [xcor] of myself[set ponto "Tras"]
        ]
        if ponto = "Direita"[right 90]
        if ponto = "Esquerda"[left 90]
        if ponto = "Tras"[right 180]

        ifelse [pcolor] of patch-right-and-ahead 90 1 != paint
        [
          right 90
          fd 1
          ask patch-here
          [
            set pcolor paint
          ]
          set nrg nrg - 2
        ]
        [
          ifelse [pcolor] of patch-right-and-ahead 180 1 != paint
          [
            right 180
            fd 1
            ask patch-here
            [
              set pcolor paint
            ]
            set nrg nrg - 2
          ]
          [
            ifelse [pcolor] of patch-left-and-ahead 90 1 != paint
            [
              left 90
              fd 1
              ask patch-here
              [
                set pcolor paint
              ]
              set nrg nrg - 2
            ]
            [
              ifelse random 101 <= 50
              [
                ifelse random 101 <= 50
                [
                  fd 1
                  set nrg nrg - 1
                ]
                [
                  right 90
                  fd 1
                  set nrg nrg - 1
                ]
              ]
              [
                ifelse random 101 <= 50
                [
                  left 90
                  fd 1
                  set nrg nrg - 1
                ]
                [
                  right 180
                  fd 1
                  set nrg nrg - 1
                ]
              ]
            ]
          ]
        ]
      ]
      [
        ifelse count (turtles-on neighbors4) with [exercito != atual and breed != bandeiras and breed != kits and breed != planes] >= 2
        [
          ifelse any? (turtles-on patch-ahead 1) with [exercito != atual and breed != bandeiras and breed != kits and breed != planes]
          [
            ifelse any? (turtles-on patch-right-and-ahead 90 1) with [exercito != atual and breed != bandeiras and breed != kits and breed != planes]
            [
              if any? (turtles-on patch-right-and-ahead 180 1) with [exercito != atual and breed != bandeiras and breed != kits and breed != planes]
              [
                left 90
                fd 2
                ask patch-here
                [
                  set pcolor paint
                ]
                set nrg nrg - 2
              ]
            ]
            [
              right 90
              fd 2
              ask patch-here
              [
                set pcolor paint
              ]
              set nrg nrg - 2
            ]
          ]
          [
            fd 2
            ask patch-here
            [
              set pcolor paint
            ]
            set nrg nrg - 2
          ]
        ]
        [
          ifelse [pcolor] of patch-right-and-ahead 90 1 != paint
          [
            right 90
            fd 1
            ask patch-here
            [
              set pcolor paint
            ]
            set nrg nrg - 2
          ]
          [
            ifelse [pcolor] of patch-right-and-ahead 180 1 != paint
            [
              right 180
              fd 1
              ask patch-here
              [
                set pcolor paint
              ]
              set nrg nrg - 2
            ]
            [
              ifelse [pcolor] of patch-left-and-ahead 90 1 != paint
              [
                left 90
                fd 1
                ask patch-here
                [
                  set pcolor paint
                ]
                set nrg nrg - 2
              ]
              [
                fd 1
                ask patch-here
                [
                  set pcolor paint
                ]
                set nrg nrg - 2
              ]
            ]
          ]
        ]
      ]
    ]
  ]
end

to check-flag
  ask bandeiras
  [
    if any? (turtles-on patch-here) with [breed != bandeiras and breed != kits and breed != planes]
    [
      ask (turtles-on patch-here) with [breed != bandeiras and breed != kits and breed != planes]
      [
        set paint color
      ]
      ask patches in-radius 5
      [
        set pcolor paint
      ]
      ifelse paint = 15
      [
        output-type (word "RED TEAM CAPTURED A FLAG\n")
        set capturasb capturasb + 1
      ]
      [
        output-type (word "TURQUOISE TEAM CAPTURED A FLAG\n")
        set capturasa capturasa + 1
      ]
      setxy random-xcor random-ycor
    ]
  ]
end











@#$#@#$#@
GRAPHICS-WINDOW
284
10
1085
812
-1
-1
13.0
1
10
1
1
1
0
1
1
1
-30
30
-30
30
1
1
1
ticks
30.0

SLIDER
10
10
182
43
lado
lado
2
max-pxcor - 1
29.0
1
1
NIL
HORIZONTAL

BUTTON
189
47
278
80
Setup
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SLIDER
9
81
181
114
soldadosB
soldadosB
0
solmax
50.0
1
1
NIL
HORIZONTAL

SLIDER
9
46
181
79
soldadosA
soldadosA
0
solmax
50.0
1
1
NIL
HORIZONTAL

SLIDER
10
116
182
149
generaisA
generaisA
0
genmax
25.0
1
1
NIL
HORIZONTAL

SLIDER
10
153
182
186
generaisB
generaisB
0
genmax
25.0
1
1
NIL
HORIZONTAL

BUTTON
190
10
278
43
Go
start\n
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
0

SLIDER
10
191
182
224
energia
energia
10
1000
1000.0
1
1
NIL
HORIZONTAL

SLIDER
10
228
182
261
evolui
evolui
1
10
10.0
1
1
NIL
HORIZONTAL

PLOT
1086
10
1629
449
Territórios
Tempo
Patches
0.0
30.0
0.0
100.0
true
true
"" ""
PENS
"Neutro" 1.0 0 -10402772 true "" "plot count patches with [pcolor != red and pcolor != turquoise]"
"A" 1.0 0 -2674135 true "" "plot count patches with [pcolor = red]"
"B" 1.0 0 -14835848 true "" "plot count patches with [pcolor = turquoise]"

MONITOR
1575
94
1642
139
A
count patches with [pcolor = red]
17
1
11

MONITOR
1575
136
1642
181
B
count patches with [pcolor = turquoise]
17
1
11

OUTPUT
1086
448
1629
603
19

BUTTON
9
299
184
332
Atualizar mundo
\nresize-world (cor * -1) cor (cor * -1) cor\nset lado cor - 1
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SWITCH
189
82
279
115
medkits
medkits
1
1
-1000

SWITCH
188
187
280
220
flag
flag
0
1
-1000

MONITOR
1575
180
1642
225
Capturas A
capturasa
17
1
11

SLIDER
10
263
182
296
cor
cor
1
30
30.0
1
1
NIL
HORIZONTAL

SLIDER
188
221
280
254
flags
flags
1
flagsmax
15.0
1
1
NIL
HORIZONTAL

SLIDER
188
116
280
149
intervalo
intervalo
60
200
60.0
5
1
NIL
HORIZONTAL

SLIDER
188
151
280
184
regen
regen
10
100
100.0
5
1
NIL
HORIZONTAL

MONITOR
1575
223
1642
268
Capturas B
capturasb
17
1
11

SWITCH
188
257
278
290
tanks?
tanks?
0
1
-1000

SLIDER
187
292
279
325
tanksA
tanksA
0
tanksmax
10.0
1
1
NIL
HORIZONTAL

SLIDER
186
326
279
359
tanksB
tanksB
0
tanksmax
10.0
1
1
NIL
HORIZONTAL

SWITCH
8
333
183
366
insanity_mode
insanity_mode
1
1
-1000

BUTTON
8
368
183
401
Atualizar valores
ifelse insanity_mode\n[\n   set solmax 1000\n   set soldadosA 1000\n   set soldadosB 1000\n   set genmax 1000\n   set generaisA 1000\n   set generaisB 1000\n   set flagsmax 1000\n   set tanksmax 1000\n   set tanksA 1000\n   set tanksB 1000\n   set kamimax 1000\n   set kamikazeA 1000\n   set kamikazeB 1000\n   set planesmax 1000\n   set planesA 1000\n   set planesB 1000\n   set minemax 1000\n   set mines 1000\n]\n[\n   set solmax 50\n   set soldadosA 50\n   set soldadosB 50\n   set genmax 25\n   set generaisA 25\n   set generaisB 25\n   set flagsmax 15\n   set flags 15\n   set tanksmax 10\n   set tanksA 10\n   set tanksB 10\n   set kamimax 30\n   set kamikazeA 30\n   set kamikazeB 30\n   set planesmax 10\n   set planesA 10\n   set planesB 10\n   set minemax 20\n   set mines 20\n]
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SWITCH
9
404
184
437
mov_alternativo
mov_alternativo
0
1
-1000

SWITCH
186
362
280
395
kamikaze?
kamikaze?
0
1
-1000

SLIDER
186
398
280
431
kamikazeA
kamikazeA
0
kamimax
30.0
1
1
NIL
HORIZONTAL

SLIDER
187
435
281
468
kamikazeB
kamikazeB
0
kamimax
30.0
1
1
NIL
HORIZONTAL

SWITCH
187
470
282
503
planes?
planes?
0
1
-1000

SLIDER
186
504
282
537
planesA
planesA
1
planesmax
10.0
1
1
NIL
HORIZONTAL

SLIDER
186
539
282
572
planesB
planesB
0
planesmax
10.0
1
1
NIL
HORIZONTAL

SWITCH
185
573
282
606
mines?
mines?
1
1
-1000

SLIDER
184
607
282
640
mines
mines
0
minemax
20.0
1
1
NIL
HORIZONTAL

@#$#@#$#@
## WHAT IS IT?

(a general understanding of what the model is trying to show or explain)

## HOW IT WORKS

(what rules the agents use to create the overall behavior of the model)

## HOW TO USE IT

(how to use the model, including a description of each of the items in the Interface tab)

## THINGS TO NOTICE

(suggested things for the user to notice while running the model)

## THINGS TO TRY

(suggested things for the user to try to do (move sliders, switches, etc.) with the model)

## EXTENDING THE MODEL

(suggested things to add or change in the Code tab to make the model more complicated, detailed, accurate, etc.)

## NETLOGO FEATURES

(interesting or unusual features of NetLogo that the model uses, particularly in the Code tab; or where workarounds were needed for missing features)

## RELATED MODELS

(models in the NetLogo Models Library and elsewhere which are of related interest)

## CREDITS AND REFERENCES

(a reference to the model's URL on the web if it has one, as well as any other necessary credits, citations, and links)
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

airplane 2
true
0
Polygon -13345367 true false 150 28 135 32 120 62 120 92 18 107 15 137 120 152 120 167 135 212 135 227 150 287 165 227 165 212 180 167 180 152 285 137 282 107 180 92 180 62 165 32
Line -6459832 false 120 30 180 30
Polygon -6459832 true false 105 255 120 240 180 240 195 255 180 270 120 270
Circle -11221820 true false 129 54 42
Rectangle -6459832 true false 147 212 152 235
Polygon -7500403 true true 23 110 119 98 120 145 23 131 26 109 39 109
Polygon -7500403 true true 182 93 186 142 278 129 276 113 181 98

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

medkit
true
15
Rectangle -1 true true 45 45 255 255
Rectangle -2674135 true false 75 120 225 180
Rectangle -2674135 true false 120 75 180 225

mine
false
0
Circle -16777216 true false 0 0 300
Circle -2674135 true false 108 108 85

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

person police
false
0
Polygon -1 true false 124 91 150 165 178 91
Polygon -13345367 true false 134 91 149 106 134 181 149 196 164 181 149 106 164 91
Polygon -13345367 true false 180 195 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285
Polygon -13345367 true false 120 90 105 90 60 195 90 210 116 158 120 195 180 195 184 158 210 210 240 195 195 90 180 90 165 105 150 165 135 105 120 90
Rectangle -7500403 true true 123 76 176 92
Circle -7500403 true true 110 5 80
Polygon -13345367 true false 150 26 110 41 97 29 137 -1 158 6 185 0 201 6 196 23 204 34 180 33
Line -13345367 false 121 90 194 90
Line -16777216 false 148 143 150 196
Rectangle -16777216 true false 116 186 182 198
Rectangle -16777216 true false 109 183 124 227
Rectangle -16777216 true false 176 183 195 205
Circle -1 true false 152 143 9
Circle -1 true false 152 166 9
Polygon -1184463 true false 172 112 191 112 185 133 179 133
Polygon -1184463 true false 175 6 194 6 189 21 180 21
Line -1184463 false 149 24 197 24
Rectangle -16777216 true false 101 177 122 187
Rectangle -16777216 true false 179 164 183 186

person police 2
false
0
Polygon -1 true false 124 91 150 165 178 91
Polygon -13345367 true false 134 91 149 106 134 181 149 196 164 181 149 106 164 91
Polygon -2064490 true false 180 195 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285
Polygon -13840069 true false 120 90 105 90 60 195 90 210 116 158 120 195 180 195 184 158 210 210 240 195 195 90 180 90 165 105 150 165 135 105 120 90
Rectangle -7500403 true true 123 76 176 92
Circle -7500403 true true 110 5 80
Polygon -13345367 true false 150 26 110 41 97 29 137 -1 158 6 185 0 201 6 196 23 204 34 180 33
Line -13345367 false 121 90 194 90
Line -16777216 false 148 143 150 196
Rectangle -16777216 true false 116 186 182 198
Rectangle -10899396 true false 109 183 124 227
Rectangle -16777216 true false 176 183 195 205
Circle -1 true false 152 143 9
Circle -1 true false 152 166 9
Polygon -1184463 true false 172 112 191 112 185 133 179 133
Polygon -1184463 true false 175 6 194 6 189 21 180 21
Line -1184463 false 149 24 197 24
Rectangle -16777216 true false 101 177 122 187
Rectangle -16777216 true false 179 164 183 186

person soldier
false
0
Rectangle -7500403 true true 127 79 172 94
Polygon -10899396 true false 105 90 60 195 90 210 135 105
Polygon -10899396 true false 195 90 240 195 210 210 165 105
Circle -7500403 true true 110 5 80
Polygon -10899396 true false 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Polygon -6459832 true false 120 90 105 90 180 195 180 165
Line -6459832 false 109 105 139 105
Line -6459832 false 122 125 151 117
Line -6459832 false 137 143 159 134
Line -6459832 false 158 179 181 158
Line -6459832 false 146 160 169 146
Rectangle -6459832 true false 120 193 180 201
Polygon -6459832 true false 122 4 107 16 102 39 105 53 148 34 192 27 189 17 172 2 145 0
Polygon -16777216 true false 183 90 240 15 247 22 193 90
Rectangle -6459832 true false 114 187 128 208
Rectangle -6459832 true false 177 187 191 208

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

sheep
false
15
Circle -1 true true 203 65 88
Circle -1 true true 70 65 162
Circle -1 true true 150 105 120
Polygon -7500403 true false 218 120 240 165 255 165 278 120
Circle -7500403 true false 214 72 67
Rectangle -1 true true 164 223 179 298
Polygon -1 true true 45 285 30 285 30 240 15 195 45 210
Circle -1 true true 3 83 150
Rectangle -1 true true 65 221 80 296
Polygon -1 true true 195 285 210 285 210 240 240 210 195 210
Polygon -7500403 true false 276 85 285 105 302 99 294 83
Polygon -7500403 true false 219 85 210 105 193 99 201 83

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

tank
true
0
Rectangle -10899396 true false 144 0 159 105
Rectangle -6459832 true false 195 45 255 255
Rectangle -16777216 false false 195 45 255 255
Rectangle -6459832 true false 45 45 105 255
Rectangle -16777216 false false 45 45 105 255
Line -16777216 false 45 75 255 75
Line -16777216 false 45 105 255 105
Line -16777216 false 45 60 255 60
Line -16777216 false 45 240 255 240
Line -16777216 false 45 225 255 225
Line -16777216 false 45 195 255 195
Line -16777216 false 45 150 255 150
Polygon -10899396 true false 90 60 60 90 60 240 120 255 180 255 240 240 240 90 210 60
Rectangle -16777216 false false 135 105 165 120
Polygon -16777216 false false 135 120 105 135 101 181 120 225 149 234 180 225 199 182 195 135 165 120
Polygon -16777216 false false 240 90 210 60 211 246 240 240
Polygon -16777216 false false 60 90 90 60 89 246 60 240
Polygon -16777216 false false 89 247 116 254 183 255 211 246 211 237 89 236
Rectangle -16777216 false false 90 60 210 90
Circle -7500403 true true 117 147 66

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

wolf
false
0
Polygon -16777216 true false 253 133 245 131 245 133
Polygon -7500403 true true 2 194 13 197 30 191 38 193 38 205 20 226 20 257 27 265 38 266 40 260 31 253 31 230 60 206 68 198 75 209 66 228 65 243 82 261 84 268 100 267 103 261 77 239 79 231 100 207 98 196 119 201 143 202 160 195 166 210 172 213 173 238 167 251 160 248 154 265 169 264 178 247 186 240 198 260 200 271 217 271 219 262 207 258 195 230 192 198 210 184 227 164 242 144 259 145 284 151 277 141 293 140 299 134 297 127 273 119 270 105
Polygon -7500403 true true -1 195 14 180 36 166 40 153 53 140 82 131 134 133 159 126 188 115 227 108 236 102 238 98 268 86 269 92 281 87 269 103 269 113

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270
@#$#@#$#@
NetLogo 6.0.2
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180
@#$#@#$#@
0
@#$#@#$#@
