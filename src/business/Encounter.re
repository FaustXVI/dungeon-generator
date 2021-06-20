open Belt;
open Peril;

type encounter = {perils: Map.t(peril, int, PerilComparator.identity)};

let newEncounter: encounter = {
  perils: Map.make(~id=(module PerilComparator)),
};

let containing = (encounter: encounter, peril: peril, number: int): encounter => {
  {perils: encounter.perils->Map.set(peril, number)};
};

let reduce =
    (encounter: encounter, accumulator: 'a, f: ('a, peril, int) => 'a): 'a => {
  encounter.perils->Map.reduce(accumulator, f);
};
