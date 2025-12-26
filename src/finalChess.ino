/**********************************************************************/
// ENGR 470: Mechatronics LED Chess Board
// By Hannah Stevenson, Maria Uribe, and Ryan Vance
// Chess algorithm based on Chessuino by Diego Cueva
/*********************************************************************/

#include <Arduino.h>
/*
  A1 == [0][3]    B1 == [0][7]    C1 == [0][11]   D1 == [0][15]
  A2 == [0][2]    B2 == [0][6]    C2 == [0][10]   D2 == [0][14]
  A3 == [0][1]    B3 == [0][5]    C3 == [0][9]    D3 == [0][13]
  A4 == [0][0]    B4 == [0][4]    C4 == [0][8]    D4 == [0][12]
  A5 == [2][12]   B5 == [2][8]    C5 == [2][4]    D5 == [2][0]
  A6 == [2][13]   B6 == [2][9]    C6 == [2][5]    D6 == [2][1]
  A7 == [2][14]   B7 == [2][10]   C7 == [2][6]    D7 == [2][2]
  A8 == [2][15]   B8 == [2][11]   C8 == [2][7]    D8 == [2][3]

  E1 == [1][3]    F1 == [1][7]    G1 == [1][11]   H1 == [1][15]
  E2 == [1][2]    F2 == [1][6]    G2 == [1][10]   H2 == [1][14]
  E3 == [1][1]    F3 == [1][5]    G3 == [1][9]    H3 == [1][13]
  E4 == [1][0]    F4 == [1][4]    G4 == [1][8]    H4 == [1][12]
  E5 == [3][12]   F5 == [3][8]    G5 == [3][4]    H5 == [3][0]
  E6 == [3][13]   F6 == [3][9]    G6 == [3][5]    H6 == [3][1]
  E7 == [3][14]   F7 == [3][10]   G7 == [3][6]    H7 == [3][2]
  E8 == [3][15]   F8 == [3][11]   G8 == [3][7]    H8 == [3][3]
*/

#define W while
#define M 0x88
#define S 128
#define I 8000

// Define constants for pieces
#define EMPTY 0
#define W_PAWN 1
#define W_KNIGHT 2
#define W_BISHOP 3
#define W_ROOK 4
#define W_QUEEN 5
#define W_KING 6
#define B_PAWN 7
#define B_KNIGHT 8
#define B_BISHOP 9
#define B_ROOK 10
#define B_QUEEN 11
#define B_KING 12

// MUX data
struct MuxChannel {
  byte mux;     // Which multiplexer (0-3)
  byte channel; // Which channel on that multiplexer (0-15)
};

// MUX variables and data
char currentMove[5] = "e2e4";
boolean blinkingActive = false;
unsigned long lastBlinkTime = 0;
bool blinkState = true;
const unsigned long BLINK_INTERVAL = 500; // Blink every 500ms

// Source and destination channels for current move
MuxChannel srcChannel;
MuxChannel dstChannel;

// Pin assignments for MUXs
const int MUX_PINS [][6] = {
  {53, 51, 49, 47, 52, 44}, //S0-S3, Sig, EN
  {29, 27, 25, 23, 46, 38},
  {45, 43, 41, 39, 50, 42},
  {37, 35, 33, 31, 48, 40}
};

// MUX channel assignments
MuxChannel getChannelFromPosition(char col, char row) {
  MuxChannel result;

  switch(col) {
    case 'a': 
      result.mux = (row > '4') ? 2 : 0; // if row > 4 mux C otherwise mux 0
      result.channel = (row > '4') ? 12 + (row - '5') : 3 - (row - '1'); 
      break;
    case 'b':
      result.mux = (row > '4') ? 2 : 0;
      result.channel = (row > '4') ? 8 + (row-'5') : 7 - (row - '1');
      break;
    case 'c':
      result.mux = (row > '4') ? 2 : 0;
      result.channel = (row > '4') ? 4 + (row - '5') : 11 - (row - '1');
      break;
    case 'd':
      result.mux = (row > '4') ? 2 : 0;
      result.channel = (row > '4') ? (row - '5') : 15 - (row - '1');
      break;
    case 'e':
      result.mux = (row > '4') ? 3 : 1; 
      result.channel = (row > '4') ? 12 + (row - '5') : 3 - (row - '1');
      break;
    case 'f':
      result.mux = (row > '4') ? 3 : 1;
      result.channel = (row > '4') ? 8 + (row - '5') : 7 - (row - '1');
      break;
    case 'g':
      result.mux = (row > '4') ? 3 : 1;
      result.channel = (row > '4') ? 4 + (row - '5') : 11 - (row - '1');
      break;
    case 'h':
      result.mux = (row > '4') ? 3 : 1;
      result.channel = (row > '4') ? (row - '5') : 15 - (row - '1');
      break;
  }
  return result;
}

// Enable a specific multiplexer and set its channel
void setMuxChannel(byte mux, byte channel) {
  // Disable all multiplexers first
  for (int i = 0; i < 4; i++) {
    digitalWrite(MUX_PINS[i][5], HIGH); // Set EN pin HIGH to disable
  }
  
  // Set the channel selection pins for the target multiplexer
  for (int i = 0; i < 4; i++) {
    digitalWrite(MUX_PINS[mux][i], (channel >> i) & 0x01);  // Set S0-S3 pins
  }
  
  // Enable only the target multiplexer
  digitalWrite(MUX_PINS[mux][5], LOW); // Set EN pin LOW to enable
}

// Turn on an LED at a specific position
void turnOnLED(byte mux, byte channel) {
  setMuxChannel(mux, channel);
  digitalWrite(MUX_PINS[mux][4], HIGH); // Set signal pin HIGH to turn on LED
}

// Turn off an LED at a specific position
void turnOffLED(byte mux, byte channel) {
  setMuxChannel(mux, channel);
  digitalWrite(MUX_PINS[mux][4], LOW); // Set signal pin LOW to turn off LED
}

// Turn off all LEDs
void turnOffAllLEDs() {
  for (int mux = 0; mux < 4; mux++) {
    digitalWrite(MUX_PINS[mux][4], LOW); // Set signal pin LOW
    digitalWrite(MUX_PINS[mux][5], HIGH); // Disable multiplexer
  }
}

// Parse a chess move and setup for blinking
void setChessMove(char move[5]) {
  // Store the move
  strncpy(currentMove, move, 5);
  
  // Get source and destination positions
  char srcCol = move[0];
  char srcRow = move[1];
  char destCol = move[2];
  char destRow = move[3];
  
  // Get multiplexer channels
  srcChannel = getChannelFromPosition(srcCol, srcRow);
  dstChannel = getChannelFromPosition(destCol, destRow);
  
  // Print debug info
  Serial.print("Move: ");
  Serial.println(move);
  Serial.print("Source: Mux ");
  Serial.print(srcChannel.mux);
  Serial.print(", Channel ");
  Serial.println(srcChannel.channel);
  Serial.print("Destination: Mux ");
  Serial.print(dstChannel.mux);
  Serial.print(", Channel ");
  Serial.println(dstChannel.channel);
  
  // Activate blinking
  blinkingActive = true;
  blinkState = true;
  lastBlinkTime = millis();
}

// Process blinking of LEDs for the current move
void updateBlink() {
  if (!blinkingActive) return;
  
  unsigned long currentTime = millis();
  
  // Check if it's time to toggle the blink state
  if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
    blinkState = !blinkState;
    lastBlinkTime = currentTime;
    
    // Turn off all LEDs first
    turnOffAllLEDs();
    
    // If blinkState is true, turn on the LEDs
    if (blinkState) {
      turnOnLED(dstChannel.mux, dstChannel.channel);
    }
    if (!blinkState) {
      turnOnLED(srcChannel.mux, srcChannel.channel);
    }
  }
}

void chessStartup() {
  for (char row = '1'; row <= '8'; row++) {
    for (char col = 'a'; col <= 'h'; col++) {
      MuxChannel channel = getChannelFromPosition(col, row);
      turnOnLED(channel.mux, channel.channel);
      delay(100);
      turnOffLED(channel.mux, channel.channel);
      delay(30);
    }
  }
}


// Board representation - standard 8x8 chess board
byte chessBoard[8][8];
String from, to;

// Captured pieces jails (max 16 pieces per side)
byte whiteCaptured[16];
byte blackCaptured[16];
int whiteCapturedCount = 0;
int blackCapturedCount = 0;

// Micro-Max chess variables:
#define MYRAND_MAX 65535     /* 16bit pseudo random generator */
long  N, T;                  /* N=evaluated positions+S, T=recursion limit */
short Q, O, K, R, k=16;      /* k=moving side */
char *p, c[5], Z;            /* p=pointer to c, c=user input, computer output, Z=recursion counter */

char L,
w[]={0,2,2,7,-1,8,12,23},                             /* relative piece values    */
o[]={-16,-15,-17,0,1,16,0,1,16,15,17,0,14,18,31,33,0, /* step-vector lists */
     7,-1,11,6,8,3,6,                                 /* 1st dir. in o[] per piece*/
     6,3,5,7,4,5,3,6};                                /* initial piece setup      */
/* board is left part, center-pts table is right part, and dummy */  

char b[]={     
  22, 19, 21, 23, 20, 21, 19, 22, 28, 21, 16, 13, 12, 13, 16, 21,
  18, 18, 18, 18, 18, 18, 18, 18, 22, 15, 10,  7,  6,  7, 10, 15,
   0,  0,  0,  0,  0,  0,  0,  0, 18, 11,  6,  3,  2,  3,  6, 11,
   0,  0,  0,  0,  0,  0,  0,  0, 16,  9,  4,  1,  0,  1,  4,  9,
   0,  0,  0,  0,  0,  0,  0,  0, 16,  9,  4,  1,  0,  1,  4,  9,
   0,  0,  0,  0,  0,  0,  0,  0, 18, 11,  6,  3,  2,  3,  6, 11,
   9,  9,  9,  9,  9,  9,  9,  9, 22, 15, 10,  7,  6,  7, 10, 15,
  14, 11, 13, 15, 12, 13, 11, 14, 28, 21, 16, 13, 12, 13, 16, 21, 0
};

char bk[16*8+1];

unsigned int seed=0;

int mn=1;
char lastH[5], lastM[5];
unsigned short ledv=1;

String inputString = "";
bool stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  lastH[0] = 0;
  Serial.println("Arduino Chess - Serial Monitor Edition");
  Serial.println("==============================================");
  Serial.println("Commands:");
  Serial.println("  'show' - Display the board");
  Serial.println("  'move e2e4' - Move a piece from e2 to e4");
  Serial.println("  'reset' - Reset the board");
  Serial.println("  'stop'  - Stop blinking");
  Serial.println();

  // Initialize all multiplexer pins
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      pinMode(MUX_PINS[i][j], OUTPUT);
    }
    // Set enable pin HIGH to disable all multiplexers initially
    digitalWrite(MUX_PINS[i][5], HIGH);
  }

  //chessStartup();
  delay(1000);
  chessStartup();
  delay(1000);

  initializeBoard();
  printBoard();
}

void loop() {
  int r;
  
  // Update LED blinking at the start of each loop iteration
  updateBlink();
  
  // Check for serial input
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if (input.startsWith("move ") && input.length() >= 9) {
      c[0] = input.charAt(5);
      c[1] = input.charAt(6);
      c[2] = input.charAt(7);
      c[3] = input.charAt(8);
      c[4] = '\0';
      
      int fromRow, fromCol, toRow, toCol;
      fromRow = '8' - c[1];
      fromCol = c[0] - 'a';
      toRow = '8' - c[3];
      toCol = c[2] - 'a';
      
      // Parse data and make human move
      K = *c - 16 * c[1] + 799, L = c[2] - 16 * c[3] + 799;
      N = 0;
      T = 0x3F;
      bkp();
      r = D(-I, I, Q, O, 1, 3);
      
      if (!(r > -I + 1)) {
        Serial.println("Lose ");
        gameOver();
      }
      
      if (k == 0x10) {
        Serial.println("No valid move");
        return;
      }
      
      strcpy(lastH, c);
    
      // Check for captured pieces
      if (chessBoard[toRow][toCol] != EMPTY) {
        addToCaptured(chessBoard[toRow][toCol]);
        Serial.print("Captured ");
        Serial.println(getPieceSymbol(chessBoard[toRow][toCol]));
      }
      
      // Check for castling and move pieces accordingly 
      if (chessBoard[fromRow][fromCol]==6 && toCol==fromCol+2){
        chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
        chessBoard[fromRow][fromCol] = EMPTY;
        chessBoard[7][5] = 4;
        chessBoard[7][7] = EMPTY;
      } else if (chessBoard[fromRow][fromCol]==6 && toCol==fromCol-2){
        chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
        chessBoard[fromRow][fromCol] = EMPTY;
        chessBoard[7][3] = 4;
        chessBoard[7][0] = EMPTY;
      }else {
        chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
        chessBoard[fromRow][fromCol] = EMPTY;
      }
      
      // Check for pawn promotion
      if(chessBoard[toRow][toCol]==1 && toRow==0){
        chessBoard[toRow][toCol] = 5;
      }

      Serial.print("Moved ");
      Serial.print(c[0]);
      Serial.print(c[1]);
      Serial.print(" to ");
      Serial.print(c[2]);
      Serial.println(c[3]);
      
      printBoard();
    
      
      mn++;
      
      // Computer's turn
      K = I;
      N = 0;
      T = 0x3F;
      r = D(-I, I, Q, O, 1, 3);
      
      if (!(r > -I + 1)) {
        Serial.println("Computer Loses");
        gameOver();
      }
      
      strcpy(lastM, c);
      Serial.print("The computer's move was ");
      Serial.println(lastM);
      
      int fromRowC, fromColC, toRowC, toColC;
      fromRowC = '8' - lastM[1];
      fromColC = lastM[0] - 'a';
      toRowC = '8' - lastM[3];
      toColC = lastM[2] - 'a';
      
      // Set up LED blinking for the computer's move
      setChessMove(lastM);
      
      // Check for captured pieces
      if (chessBoard[toRowC][toColC] != EMPTY) {
        addToCaptured(chessBoard[toRowC][toColC]);
        Serial.print("Captured ");
        Serial.println(getPieceSymbol(chessBoard[toRowC][toColC]));
      }

      // Check for castling and move pieces accordingly: 
      if (chessBoard[fromRowC][fromColC]==12 && toColC==fromColC+2){
        chessBoard[toRowC][toColC] = chessBoard[fromRowC][fromColC];
        chessBoard[fromRowC][fromColC] = EMPTY;
        chessBoard[0][5] = 10;
        chessBoard[0][7] = EMPTY;
      } else if (chessBoard[fromRowC][fromColC]==12 && toColC==fromColC-2){
        chessBoard[toRowC][toColC] = chessBoard[fromRowC][fromColC];
        chessBoard[fromRowC][fromColC] = EMPTY;
        chessBoard[0][3] = 10;
        chessBoard[0][0] = EMPTY;
      } else {
        chessBoard[toRowC][toColC] = chessBoard[fromRowC][fromColC];
        chessBoard[fromRowC][fromColC] = EMPTY;
      }

      // Check for pawn promotion
      if(chessBoard[toRowC][toColC]==7 && toRowC==7){
        chessBoard[toRowC][toColC] = 11;
      }
      printBoard();
    } 

    else if (input.equals("stop")) {
      blinkingActive = false;
      turnOffAllLEDs();
      Serial.println("Blinking stopped");
    }
    else if (input.equals("show")) {
      printBoard();
    }
    else if (input.equals("reset")) {
      initializeBoard();
      printBoard();
      Serial.println("Board reset to initial position.");
      chessStartup();
    }
    else {
      Serial.println("Unknown command. Try 'show', 'move e2e4', 'reset', or 'stop'.");
    }
  }
}


// User interface routines from Micro-Max chess

unsigned short myrand(void) {
  unsigned short r = (unsigned short)(seed % MYRAND_MAX);
  return r = ((r << 11) + (r << 7) + r) >> 1;
}
/* recursive minimax search */
/* (q,l)=window, e=current eval. score, */
/* E=e.p. sqr.z=prev.dest, n=depth; return score */
short D(short q, short l, short e, unsigned char E, unsigned char z, unsigned char n) {
  short m, v, i, P, V, s;
  unsigned char t, p, u, x, y, X, Y, H, B, j, d, h, F, G, C;
  signed char r;
  if (++Z > 30) {                                   /* stack underrun check */
    --Z; return e;
  }
  q--;                                          /* adj. window: delay bonus */
  k ^= 24;                                      /* change sides             */
  d = Y = 0;                                    /* start iter. from scratch */
  X = myrand() & ~M;                            /* start at random field    */
  W(d++ < n || d < 3 ||                         /* iterative deepening loop */
    z & K == I && (N < T & d < 98 ||            /* root: deepen upto time   */
                   (K = X, L = Y & ~M, d = 3)))                /* time's up: go do best    */
  { x = B = X;                                   /* start scan at prev. best */
    h = Y & S;                                   /* request try noncastl. 1st*/
    P = d < 3 ? I : D(-l, 1 - l, -e, S, 0, d - 3); /* Search null move         */
    m = -P < l | R > 35 ? d > 2 ? -I : e : -P;   /* Prune or stand-pat       */
    ++N;                                         /* node count (for timing)  */
    do {
      u = b[x];                                   /* scan board looking for   */
      if (u & k) {                                /*  own piece (inefficient!)*/
        r = p = u & 7;                             /* p = piece type (set r>0) */
        j = o[p + 16];                             /* first step vector f.piece*/
        W(r = p > 2 & r < 0 ? -r : -o[++j])        /* loop over directions o[] */
        { A:                                        /* resume normal after best */
          y = x; F = G = S;                         /* (x,y)=move, (F,G)=castl.R*/
          do {                                      /* y traverses ray, or:     */
            H = y = h ? Y ^ h : y + r;               /* sneak in prev. best move */
            if (y & M)break;                         /* board edge hit           */
            m = E - S & b[E] && y - E < 2 & E - y < 2 ? I : m; /* bad castling             */
            if (p < 3 & y == E)H ^= 16;              /* shift capt.sqr. H if e.p.*/
            t = b[H]; if (t & k | p < 3 & !(y - x & 7) - !t)break; /* capt. own, bad pawn mode */
            i = 37 * w[t & 7] + (t & 192);           /* value of capt. piece t   */
            m = i < 0 ? I : m;                       /* K capture                */
            if (m >= l & d > 1)goto C;               /* abort on fail high       */
            v = d - 1 ? e : i - p;                   /* MVV/LVA scoring          */
            if (d - !t > 1)                          /* remaining depth          */
            { v = p < 6 ? b[x + 8] - b[y + 8] : 0;    /* center positional pts.   */
              b[G] = b[H] = b[x] = 0; b[y] = u | 32;  /* do move, set non-virgin  */
              if (!(G & M))b[F] = k + 6, v += 50;     /* castling: put R & score  */
              v -= p - 4 | R > 29 ? 0 : 20;           /* penalize mid-game K move */
              if (p < 3)                              /* pawns:                   */
              { v -= 9 * ((x - 2 & M || b[x - 2] - u) + /* structure, undefended    */
                          (x + 2 & M || b[x + 2] - u) - 1  /*        squares plus bias */
                          + (b[x ^ 16] == k + 36))          /* kling to non-virgin King */
                     - (R >> 2);                       /* end-game Pawn-push bonus */
                V = y + r + 1 & S ? 647 - p : 2 * (u & y + 16 & 32); /* promotion or 6/7th bonus */
                b[y] += V; i += V;                     /* change piece, add score  */
              }
              v += e + i; V = m > q ? m : q;          /* new eval and alpha       */
              C = d - 1 - (d > 5 & p > 2 & !t & !h);
              C = R > 29 | d < 3 | P - I ? C : d;     /* extend 1 ply if in check */
              do
                s = C > 2 | v > V ? -D(-l, -V, -v,     /* recursive eval. of reply */
                                       F, 0, C) : v;    /* or fail low if futile    */
              W(s > q&++C < d); v = s;
              if (z && K - I && v + I && x == K & y == L) /* move pending & in root:  */
              { Q = -e - i; O = F;                     /*   exit if legal & found  */
                R += i >> 7; --Z; return l;            /* captured non-P material  */
              }
              b[G] = k + 6; b[F] = b[y] = 0; b[x] = u; b[H] = t; /* undo move,G can be dummy */
            }
            if (v > m)                               /* new best, update max,best*/
              m = v, X = x, Y = y | S & F;            /* mark double move with S  */
            if (h) {
              h = 0;  /* redo after doing old best*/
              goto A;
            }
            if (x + r - y | u & 32 |                 /* not 1st step,moved before*/
                p > 2 & (p - 4 | j - 7 ||             /* no P & no lateral K move,*/
                         b[G = x + 3 ^ r >> 1 & 7] - k - 6     /* no virgin R in corner G, */
                         || b[G ^ 1] | b[G ^ 2])               /* no 2 empty sq. next to R */
               )t += p < 5;                           /* fake capt. for nonsliding*/
            else F = y;                              /* enable e.p.              */
          } W(!t);                                  /* if not capt. continue ray*/
        }
      }
    } W((x = x + 9 & ~M) - B);                 /* next sqr. of board, wrap */
C: if (m > I - M | m < M - I)d = 98;           /* mate holds to any depth  */
    m = m + I | P == I ? m : 0;                  /* best loses K: (stale)mate*/
    if (z && d > 2)
    { *c = 'a' + (X & 7); c[1] = '8' - (X >> 4); c[2] = 'a' + (Y & 7); c[3] = '8' - (Y >> 4 & 7); c[4] = 0;
      char buff[150];
    }
  }                                             /*    encoded in X S,8 bits */
  k ^= 24;                                      /* change sides back        */
  --Z; return m += m < e;                       /* delayed-loss bonus       */
}
void gameOver() {
  for (;;);
}
void bkp() {
  for (int i = 0; i < 16 * 8 + 1; i++) {
    bk[i] = b[i];
  }
}

// Piece symbols for display in serial monitor
char getPieceSymbol(byte piece) {
  switch (piece) {
    case EMPTY: return ' ';
    case W_PAWN: return 'P';
    case W_KNIGHT: return 'N';
    case W_BISHOP: return 'B';
    case W_ROOK: return 'R';
    case W_QUEEN: return 'Q';
    case W_KING: return 'K';
    case B_PAWN: return 'p';
    case B_KNIGHT: return 'n';
    case B_BISHOP: return 'b';
    case B_ROOK: return 'r';
    case B_QUEEN: return 'q';
    case B_KING: return 'k';
    default: return '?';
  }
}

// Function to check if a piece is white
boolean isWhite(byte piece) {
  return piece >= W_PAWN && piece <= W_KING;
}

// Function to check if a piece is black
boolean isBlack(byte piece) {
  return piece >= B_PAWN && piece <= B_KING;
}

// Initialize the board with starting positions
void initializeBoard() {
  // Clear the board
 char resetb[]={     
  22, 19, 21, 23, 20, 21, 19, 22, 28, 21, 16, 13, 12, 13, 16, 21,
  18, 18, 18, 18, 18, 18, 18, 18, 22, 15, 10,  7,  6,  7, 10, 15,
   0,  0,  0,  0,  0,  0,  0,  0, 18, 11,  6,  3,  2,  3,  6, 11,
   0,  0,  0,  0,  0,  0,  0,  0, 16,  9,  4,  1,  0,  1,  4,  9,
   0,  0,  0,  0,  0,  0,  0,  0, 16,  9,  4,  1,  0,  1,  4,  9,
   0,  0,  0,  0,  0,  0,  0,  0, 18, 11,  6,  3,  2,  3,  6, 11,
   9,  9,  9,  9,  9,  9,  9,  9, 22, 15, 10,  7,  6,  7, 10, 15,
  14, 11, 13, 15, 12, 13, 11, 14, 28, 21, 16, 13, 12, 13, 16, 21, 0
  };

  for (int i = 0; i < 16 * 8 + 1; i++) {
    b[i] = resetb[i];
  }

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      chessBoard[row][col] = EMPTY;
    }
  }
  
  // Clear captured pieces
  whiteCapturedCount = 0;
  blackCapturedCount = 0;
  
  // Set up pawns
  for (int col = 0; col < 8; col++) {
    chessBoard[1][col] = B_PAWN;  // Black pawns on rank 2
    chessBoard[6][col] = W_PAWN;  // White pawns on rank 7
  }
  
  // Set up black pieces on rank 1
  chessBoard[0][0] = B_ROOK;
  chessBoard[0][1] = B_KNIGHT;
  chessBoard[0][2] = B_BISHOP;
  chessBoard[0][3] = B_QUEEN;
  chessBoard[0][4] = B_KING;
  chessBoard[0][5] = B_BISHOP;
  chessBoard[0][6] = B_KNIGHT;
  chessBoard[0][7] = B_ROOK;
  
  // Set up white pieces on rank 8
  chessBoard[7][0] = W_ROOK;
  chessBoard[7][1] = W_KNIGHT;
  chessBoard[7][2] = W_BISHOP;
  chessBoard[7][3] = W_QUEEN;
  chessBoard[7][4] = W_KING;
  chessBoard[7][5] = W_BISHOP;
  chessBoard[7][6] = W_KNIGHT;
  chessBoard[7][7] = W_ROOK;
}

// Print the current board state to serial monitor in 8x12 format
void printBoard() {
  Serial.println("\n  +----JAIL----+---+-- CHESS BOARD --+----JAIL----+");
  
  // Print column headers for chess board
  Serial.println("  |            |   | a b c d e f g h |            |");
  Serial.println("  +------------+---+-----------------+------------+");
  
  for (int row = 0; row < 8; row++) {
    // Print row number for chess board
    Serial.print("  |");
    
    // Print left jail (black captured pieces)
    int blackIndex = row;
    int blackIndex2 = row + 8;                                                   
    if (blackIndex < blackCapturedCount) {
      Serial.print(" ");
      Serial.print(getPieceSymbol(blackCaptured[blackIndex]));
      Serial.print("  ");
      if (blackIndex2 < blackCapturedCount) {
        Serial.print(getPieceSymbol(blackCaptured[blackIndex2]));
      } else {Serial.print(" ");}
      Serial.print("       ");
    } else {
      Serial.print("            ");
    }
    
    Serial.print("| ");
    
    // Print row number
    Serial.print(8 - row);
    Serial.print(" | ");
    
    // Print chess board row
    for (int col = 0; col < 8; col++) {
      Serial.print(getPieceSymbol(chessBoard[row][col]));
      Serial.print(" ");
    }
    
    Serial.print("| ");
    
    // Print right jail (white captured pieces)
    int whiteIndex = row;
    int whiteIndex2 = row + 8;
    if (whiteIndex < whiteCapturedCount) {
      Serial.print(" ");
      Serial.print(getPieceSymbol(whiteCaptured[whiteIndex]));
      Serial.print("  ");
      if(whiteIndex2 < whiteCapturedCount) {
        Serial.print(getPieceSymbol(whiteCaptured[whiteIndex2]));
      } else {Serial.print(" ");}
      Serial.print("      ");
    } else {
      Serial.print("           ");
    }
    
    Serial.println("|");
  }
  
  Serial.println("  +------------+---+-----------------+------------+");
  Serial.println("  |  P1  Jail  |   |                 |  P2  Jail  |");
  Serial.println("  +------------+---+-----------------+------------+");
  Serial.println();
}

// Add a piece to the appropriate jail
void addToCaptured(byte piece) {
  if (isWhite(piece)) {
    // Add white piece to black's jail (right side)
    whiteCaptured[whiteCapturedCount++] = piece;
  } else if (isBlack(piece)) {
    // Add black piece to white's jail (left side)
    blackCaptured[blackCapturedCount++] = piece;
  }
}
