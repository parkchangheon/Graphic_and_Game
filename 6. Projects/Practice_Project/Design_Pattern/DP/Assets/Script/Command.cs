using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Command //명령을 내리는 객체~
{
    public virtual void Execute(Actor actor) { }
    public virtual void Undo(Actor actor) { }
}

public class MoveLeft : Command
{
    public MoveLeft() { }
    public override void Execute(Actor actor) 
    {
        actor.Left(); 
    }
}

public class MoveRight : Command
{
    public MoveRight() { }
    public override void Execute(Actor actor) 
    {
        actor.Right(); 
    }
}

public class MoveUp : Command
{
    public MoveUp() { }
    public override void Execute(Actor actor) 
    {
        actor.Up(); 
    }
}

public class MoveDown : Command
{
    public MoveDown() { }
    public override void Execute(Actor actor) 
    {
        actor.Down(); 
    }
}

public class CommandFire : Command
{
    public override void Execute(Actor actor) { actor.Fire(); }
}

public class CommandJump : Command
{
    public override void Execute(Actor actor) { actor.Jump(); }
}

public class CommandRoll : Command {
    public override void Execute(Actor actor) { actor.Roll(); }
}

public class CommandSkill : Command
{
    public override void Execute(Actor actor) { actor.Skill(); }
}