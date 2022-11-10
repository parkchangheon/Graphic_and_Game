using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Actor   //액터의 메소드들을 정의한다.
{
    public void Left() { Debug.Log("Left"); }
    public void Right() { Debug.Log("Right"); }
    public void Up() { Debug.Log("Up"); }
    public void Down() { Debug.Log("Down"); }

    public void Fire() { Debug.Log("Fire"); }
    public void Jump() { Debug.Log("jump"); }
    public void Roll() { Debug.Log("Roll"); }
    public void Skill() { Debug.Log("Skill"); }
}


public class Cube : MonoBehaviour
{
    public enum eBtn
    {
        left,
        right,
        up,
        down,
        jump,
        fire,
        roll,
        skill,
        None
    }

    eBtn pressedBtn = eBtn.None;
    Command ML, MR, MU, MD, AJ, AF, AR, AS;
    Actor actor;

    void Start() {
        actor = new Actor();
        setCommand();
    }

    void setCommand(){
        ML = new MoveLeft();
        MR = new MoveRight();
        MU = new MoveUp();
        MD = new MoveDown();

        AF = new CommandFire();
        AJ = new CommandJump();
        AR = new CommandRoll();
        AS = new CommandSkill();
    }

    void Update()
    {
        Command command = GetCommand();
        if (command != null)
            command.Execute(actor);
    }

    Command GetCommand()
    {
        if (IsPressed(eBtn.left)) return ML;
        else if (IsPressed(eBtn.right)) return MR;
        else if (IsPressed(eBtn.up)) return MU;
        else if (IsPressed(eBtn.down)) return MD;
        else if (IsPressed(eBtn.jump)) return AJ;
        else if (IsPressed(eBtn.roll)) return AR;
        else if (IsPressed(eBtn.fire)) return AF;
        else if (IsPressed(eBtn.skill)) return AS;

        return null;
    }

    bool IsPressed(eBtn btn)
    {
        pressedBtn = eBtn.None;

        if (Input.GetKey("a"))
            pressedBtn = eBtn.left;
        else if (Input.GetKey("d"))
            pressedBtn = eBtn.right;
        else if (Input.GetKey("w"))
            pressedBtn = eBtn.up;
        else if (Input.GetKey("s"))
            pressedBtn = eBtn.down;
        else if (Input.GetKeyDown(KeyCode.Space))  // action
            pressedBtn = eBtn.right;
        else if (Input.GetMouseButton(0))
            pressedBtn = eBtn.fire;
        else if (Input.GetKey(KeyCode.LeftControl))
            pressedBtn = eBtn.roll;
        else if (Input.GetKey("q"))
            pressedBtn = eBtn.skill;

        return (btn == pressedBtn);
    }

}
