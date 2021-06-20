open Belt;

type level =
  | GroupLevelMinus1
  | GroupLevel;

type perilType =
  | Creature
  | SimpleDanger
  | ComplexDanger;

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
