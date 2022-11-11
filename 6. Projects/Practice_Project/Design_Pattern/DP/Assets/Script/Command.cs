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
    public MoveLeft(Vector3 movePos) { _movePos = movePos; }
    Vector3 prevPos = Vector3.zero;
    private Vector3 _movePos;

    public override void Execute(Actor actor) 
    {
        prevPos = actor.transform.position;
        actor.Left(_movePos); 
    }

    public override void Undo(Actor actor)
    {
        actor.Left(prevPos);
    }

}

public class MoveRight : Command
{
    public MoveRight(Vector3 movePos) { _movePos = movePos; }
    Vector3 prevPos = Vector3.zero;
    private Vector3 _movePos;

    public override void Execute(Actor actor) 
    {
        prevPos = actor.transform.position;
        actor.Right(_movePos); 
    }
}

public class MoveUp : Command
{
    public MoveUp(Vector3 movePos) { _movePos = movePos; }
    Vector3 prevPos = Vector3.zero;
    private Vector3 _movePos;

    public override void Execute(Actor actor) 
    {
        prevPos = actor.transform.position;
        actor.Up(_movePos); 
    }
}

public class MoveDown : Command
{
    public MoveDown(Vector3 movePos) { _movePos = movePos; }
    Vector3 prevPos = Vector3.zero;
    private Vector3 _movePos;

    public override void Execute(Actor actor) 
    {
        prevPos = actor.transform.position;
        actor.Down(_movePos); 
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