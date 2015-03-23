'Road Demonstration Program by Louis Gorenfeld 2010

'This program is intended to show concepts described at Lou's Pseudo 3d Page
'http://www.gorenfeld.net/lou/pseudo

'It defaults to generating 80 frames during which the road curves right,
'uncurves, and repeats.  It lasts several seconds running under DOSBox at
'12000 cycles and 0 frameskip on a Mac Mini 2.0GHz dual core

'I've left much detail off of the road.  You can draw them in around line 70!
'Happy coding! :)

CONST RoadLines = 99
CONST ScrollSpeed = 10
CONST RoadY = -1        'arbitrary
CONST ResX = 320
CONST ResY = 200
CONST PlrLine = 8       'What line is the player sprite on?
DIM ZMap(RoadLines) AS SINGLE

' Initialize ZMap
FOR A = 1 TO RoadLines
        ZMap(A) = RoadY / (A - (ResY / 2))
NEXT A

' Normalize ZMap so the line with the player on it is scale=1 (or would be
' If we had a player sprite :))
b = 1 / ZMap(PlrLine)
b = b * 100   'in percents because QBasic's MOD is lame
FOR A = 1 TO RoadLines
        ZMap(A) = ZMap(A) * b
NEXT A

' 320x200x4bpp
SCREEN 7

' Draw the road
DIM X AS SINGLE
DIM DX AS SINGLE
DIM DDX AS SINGLE
DIM HalfWidth AS SINGLE
DIM SegY AS SINGLE
NextStretch$ = "Straight"

CONST WidthStep = 1

FOR A = 1 TO ResY - RoadLines
      LINE (0, A)-(ResX - 1, A), 9
NEXT A

TexOffset = 100
SegY = RoadLines
DX = 0
DDX = .02    ' This controls the steepness of the curve

FOR C = 1 TO 80

' Set up the frame
X = ResX / 2
DX = 0
HalfWidth = 120
ScreenLine = ResY - 1

FOR A = 1 TO RoadLines
        IF (ZMap(A) + TexOffset) MOD 100 > 50 THEN
                GrassColor = 10
                RoadColor = 7
        ELSE
                GrassColor = 2
                RoadColor = 8
        END IF

        LINE (X - HalfWidth, ScreenLine)-(X + HalfWidth, ScreenLine), RoadColor
        LINE (0, ScreenLine)-(X - HalfWidth, ScreenLine), GrassColor
        LINE (X + HalfWidth, ScreenLine)-(ResX - 1, ScreenLine), GrassColor
        HalfWidth = HalfWidth - WidthStep
        ScreenLine = ScreenLine - 1

        IF NextStretch$ = "Straight" THEN
                IF A > SegY THEN
                       DX = DX + DDX
                END IF
        ELSEIF NextStretch$ = "Curved" THEN
                IF A < SegY THEN
                       DX = DX + DDX
                END IF
        END IF
        X = X + DX
NEXT A

' Wrap positions (fractional):

TexOffset = TexOffset + ScrollSpeed
WHILE TexOffset >= 100
        TexOffset = TexOffset - 100
WEND

SegY = SegY - 5  ' Decrease SegY by an arbitrary amount.  Adjust to taste.
WHILE SegY < 0
        SegY = SegY + RoadLines
        IF NextStretch$ = "Curved" THEN
                NextStretch$ = "Straight"
        ELSEIF NextStretch$ = "Straight" THEN
                NextStretch$ = "Curved"
        END IF
WEND

NEXT C

