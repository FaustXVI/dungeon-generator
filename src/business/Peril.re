open Belt;

type level =
  | GroupLevelMinus2
  | GroupLevelMinus1
  | GroupLevel
  | GroupLevelPlus1;

let levels = [
  GroupLevelMinus2,
  GroupLevelMinus1,
  GroupLevel,
  GroupLevelPlus1,
];

type perilType =
  | Creature
  | SimpleDanger
  | ComplexDanger;

let perilTypes = [Creature, SimpleDanger, ComplexDanger];

type peril = {
  perilType,
  level,
};

let aPeril = (perilType: perilType, level: level): peril => {
  {perilType, level};
};

let perilTypeOf = (peril: peril): perilType => {
  peril.perilType;
};

let levelOf = (peril: peril): level => {
  peril.level;
};

module PerilComparator =
  Id.MakeComparable({
    type t = peril;
    let cmp = (a: peril, b: peril) =>
      switch (compare(perilTypeOf(a), perilTypeOf(b))) {
      | 0 => compare(levelOf(a), levelOf(b))
      | x => x
      };
  });

let experiencePointsForSimpleDanger = (level: level) => {
  switch (level) {
  | GroupLevelMinus2 => 4
  | GroupLevelMinus1 => 6
  | GroupLevel => 8
  | GroupLevelPlus1 => 12
  };
};

let experiencePointsForCreatureAndComplexDanger = (level: level) => {
  switch (level) {
  | GroupLevelMinus2 => 20
  | GroupLevelMinus1 => 30
  | GroupLevel => 40
  | GroupLevelPlus1 => 60
  };
};

let experiencePointForPeril = (peril: peril) => {
  switch (peril) {
  | {perilType: SimpleDanger, level} =>
    experiencePointsForSimpleDanger(level)
  | {perilType: Creature | ComplexDanger, level} =>
    experiencePointsForCreatureAndComplexDanger(level)
  };
};
