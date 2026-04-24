## Solid Principles

- Single Responsibility Principle (SRP)
- Open/Closed Principle (OCP)
- Dependency Inversion Principle (DIP)

## 1. SRP
A class should have one responsiblity

The best example of SRP in this project is the Observer system :

Observer -> only defines notification behaviour

Key & Collectible -> only define what happens when picked up

Why this follows SRP

- Key & Collectible does'nt manage observers directly
- Observer does'nt know about items or gameplay

Each class changes only if its specific role changes

### How this improved the code

- Makes the code easier to understand and maintain
- Bugs are easier to isolate because each class has a clear role
- The Observer system is reusable in other parts of the project

### Downsides

- Introduces more classes which increases complexity
- Requires more planning to separate responsibilities correctly

## 2. OCP
A class should be open for extension but closed for modification

The best example of OCP in this project is the Item system :

Item -> acts as a base abstract class

Key & Collectible -> extend Item with their own behaviour

Why this follows OCP

- New item types can be added without changing existing code
- The base Item class remains unchanged

### How this improved the code

- Makes it easy to add new item types without breaking existing code
- Reduces risk of introducing bugs when adding features
- Encourages a modular design

### Downsides

- Can result in many small classes
- Requires thinking ahead about abstraction

## 3. DIP
high-level modules should not depend on low-level modules

The best example of DIP in this project is how Level interacts with Items :

Level -> stores and interacts with a collection of Item objects

Item -> acts as an abstraction for all item types

Key & Collectible -> concrete implementations of Item

Why this follows DIP

- Level depends on the Item abstraction instead of concrete classes
- Key and Collectible can be used interchangeably through Item
- High level logic (Level) is decoupled from specific item implementations

### How this improved the code

- Makes the system more flexible and easier to extend
- Reduces tight coupling between Level and specific item types
- Allows new item types to be introduced with minimal changes

### Downsides

- Adds extra abstraction which can make the code harder to understand
