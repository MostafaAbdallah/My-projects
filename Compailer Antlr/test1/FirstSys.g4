grammar FirstSys;

prog: axiom production+ angle lineLenght iteration;

axiom: 'axiom' lstr+;

lstr: ID | '+' | '-' | '['lstr+']';

production: 'production' ID '->' lstr+;

angle: 'angle' '=' (FLOAT | INT);

lineLenght: 'lenght' '=' (FLOAT | INT);

iteration: 'iterations' '=' INT;

ID: [A-Z] | [a-z];

FLOAT: [0-9]+.[0-9]+;

INT: [0-9]+;


WS: [ \t\r\n]+ -> skip;