# Gladiator Arena Simulation

## Overview
Gladiator Arena Simulation is a combat strategy game created in C++. The game mimics a gladiatorial combat scenario where players of different classes - Human, Beast, Berserker, and Squad engage in battles. Each class has unique attributes and skills that significantly impact the battle's outcome.

### Player Classes:

- **Human**: Representing a human gladiator, this class includes health, attack strength, agility, and defense attributes. A human can endure damage and also gain improved attack and agility after a successful combat.

- **Beast**: The Beast class has health, attack, and agility attributes much like a human but lacks a defense attribute. However, when their health falls below a certain limit, their attack power doubled.

- **Berserker**: Berserker is a hybrid of humans and beasts and demonstrates the concept of multiple inheritance in action. A berserker's behavior changes between that of a beast and a human depending on its health status.

#### Composite Player Class:

- **Squad** : Squads are composite teams of players that fight collectively. A squad's properties, such as total damage dispersion and agility, are determined by its member players.

The game also features an Arena - where the battles take place, and Caesar - who can decide the fate of the players.

## Personal Background
This software was originally developed as a part of a university programming assignment. It provided insights into fundamental concepts like Object-Oriented Programming, encapsulation, inheritance, polymorphism, and data structures (linked lists).
