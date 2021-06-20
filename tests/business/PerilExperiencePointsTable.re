open Belt;
open Peril;
let allPerilDescriptions: List.t((perilType, level, string, int)) = [
  (Creature, GroupLevel, "Creature at group level", 40),
  (SimpleDanger, GroupLevel, "Simple Danger at group level", 8),
  (ComplexDanger, GroupLevel, "Complex Danger at group level", 40),
  (Creature, GroupLevelMinus1, "Creature -1", 30),
  (SimpleDanger, GroupLevelMinus1, "Simple Danger -1", 6),
  (ComplexDanger, GroupLevelMinus1, "Complex Danger -1", 30),
  (Creature, GroupLevelPlus1, "Creature +1", 60),
  (SimpleDanger, GroupLevelPlus1, "Simple Danger +1", 12),
  (ComplexDanger, GroupLevelPlus1, "Complex Danger +1", 60),
];

let perilTable =
  allPerilDescriptions->List.map(((p, l, _, _)) => {aPeril(p, l)});

let perilExperiencePointsTable =
  allPerilDescriptions->List.map(((p, l, _, xp)) => {(aPeril(p, l), xp)});

let perilLabelsTable =
  allPerilDescriptions->List.map(((p, l, label, _)) => {
    (aPeril(p, l), label)
  });
