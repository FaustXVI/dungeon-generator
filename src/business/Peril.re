open Belt;

type level =
  | GroupLevelMinus1
  | GroupLevel;

let levels = [GroupLevel, GroupLevelMinus1];

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

let experiencePointForPeril = (peril: peril) => {
  switch (peril) {
  | {perilType: SimpleDanger, level: GroupLevelMinus1} => 6
  | {perilType: SimpleDanger, level: GroupLevel} => 8
  | {perilType: Creature, _}
  | {perilType: ComplexDanger, _} => 40
  };
};
