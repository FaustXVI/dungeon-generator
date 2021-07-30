open Belt

type level =
  | GroupLevelMinus4
  | GroupLevelMinus3
  | GroupLevelMinus2
  | GroupLevelMinus1
  | GroupLevel
  | GroupLevelPlus1
  | GroupLevelPlus2
  | GroupLevelPlus3
  | GroupLevelPlus4

let levels = [
  GroupLevelMinus4,
  GroupLevelMinus3,
  GroupLevelMinus2,
  GroupLevelMinus1,
  GroupLevel,
  GroupLevelPlus1,
  GroupLevelPlus2,
  GroupLevelPlus3,
  GroupLevelPlus4,
]

type perilType =
  | Creature
  | SimpleDanger
  | ComplexDanger

let perilTypes = [Creature, SimpleDanger, ComplexDanger]

type peril = {
  perilType: perilType,
  level: level,
}

let aPeril = (perilType: perilType, level: level): peril => {
  {perilType: perilType, level: level}
}

let perilTypeOf = (peril: peril): perilType => {
  peril.perilType
}

let levelOf = (peril: peril): level => {
  peril.level
}

module PerilComparator = Id.MakeComparable({
  type t = peril
  let cmp = (a: peril, b: peril) =>
    switch compare(perilTypeOf(a), perilTypeOf(b)) {
    | 0 => compare(levelOf(a), levelOf(b))
    | x => x
    }
})

let experiencePointsForSimpleDanger = (level: level) => {
  switch level {
  | GroupLevelMinus4 => 2
  | GroupLevelMinus3 => 3
  | GroupLevelMinus2 => 4
  | GroupLevelMinus1 => 6
  | GroupLevel => 8
  | GroupLevelPlus1 => 12
  | GroupLevelPlus2 => 16
  | GroupLevelPlus3 => 24
  | GroupLevelPlus4 => 32
  }
}

let experiencePointsForCreatureAndComplexDanger = (level: level) => {
  switch level {
  | GroupLevelMinus4 => 10
  | GroupLevelMinus3 => 15
  | GroupLevelMinus2 => 20
  | GroupLevelMinus1 => 30
  | GroupLevel => 40
  | GroupLevelPlus1 => 60
  | GroupLevelPlus2 => 80
  | GroupLevelPlus3 => 120
  | GroupLevelPlus4 => 160
  }
}

let experiencePointForPeril = (peril: peril) => {
  switch peril {
  | {perilType: SimpleDanger, level} => experiencePointsForSimpleDanger(level)
  | {perilType: Creature | ComplexDanger, level} =>
    experiencePointsForCreatureAndComplexDanger(level)
  }
}

exception UnexpectedCondition(string)

let smallestPeril = (perils: list<peril>): peril => {
  let cmp = (a: peril, b: peril) => experiencePointForPeril(a) - experiencePointForPeril(b)
  let sortedPerils = List.sort(perils, cmp)
  switch List.head(sortedPerils) {
  | None => raise(UnexpectedCondition("empty peril list"))
  | Some(p) => p
  }
}