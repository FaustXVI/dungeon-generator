# Architecture Decision Record

## Characteristics of a good ADR:

- Point in Time - Identify when the AD was made
- Rationality - Explain the reason for making the particular AD
- Immutable record - The decisions made in a previously published ADR should not be altered
- Specificity - Each ADR should be about a single AD

## Characteristics of a good context in an ADR:

- Explain your organization's situation and business priorities
- Include rationale and considerations based on social and skills makeups of your teams

## Characteristics of good Consequences in an ADR::

- Right approach - "We need to start doing X instead of Y"
- Wrong approach - Do not explain the AD in terms of "Pros" and "Cons" of having made the particular AD

## A new ADR may take the place of a previous ADR:

- When an AD is made that replaces or invalidates a previous ADR, a new ADR should be created


## Decisions taken before May 16

### Develop a web app : matching the occasion to develop with ReasonML & ReactReason with a need for a D&D creation helper tool.

### Use ReasonML and React Reason : fun, learning

### Checking the integration between GUI and Business, when GUI has no logic of its own, can be done through a quick visual testing

Works at least for simple applications.

Test First approach is still feasible : we can start the session by acknowledging that the GUI is not working yet. 

Tracks for future improvement :
- would curl and diff do the trick of checking GUI/Business wiring ? (think "smoke test")
- or approval testing (Jest's snapshots)
- or fully integraded jest test but with very 'light' assertions (not revealing too much)

When it this decision becoming too naïve ? (when we could not spot a defect in the wiring ?)

### Design separates Business domain and infrastructure

Business domain objects are purely functional values

### Random is a resource for domain values, hence a dependency, not a part of a domain value

(the way to use random for randomizing the values is still in debate)




