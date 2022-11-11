using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Actor   //명령을 실행하는 객체?
{
    public Vector3 pos = new Vector3(0, 0, 0);
    public Transform transform;
    public Actor(Transform tr)
    {
        transform = tr;
    }

    public void Left(Vector3 pos)
    {
        Debug.Log("Left");
        transform.position += pos;
    }
    public void Right(Vector3 pos) 
    {
        Debug.Log("Right");
        transform.position += pos;
    }
    public void Up(Vector3 pos) 
    { 
        Debug.Log("Up");
        transform.position += pos;
    }
    public void Down(Vector3 pos) 
    {
        Debug.Log("Down");
        transform.position += pos;
    }
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
    [SerializeField] public Actor actor;
    [SerializeField] private float moveSpeed = 0.02f;
    Stack<Command> stack = new Stack<Command>();
    bool isPushUndoKey = false;


    void Start() {
        actor = new Actor(gameObject.transform); //여기에서 게임 오브젝트의 트랜스폼을 전달.
        setCommand();
    }

    void setCommand(){
        ML = new MoveLeft(new Vector3(-moveSpeed, 0, 0));
        MR = new MoveRight(new Vector3(moveSpeed, 0, 0));
        MU = new MoveUp(new Vector3(0, moveSpeed, 0));
        MD = new MoveDown(new Vector3(0, -moveSpeed, 0));

        AF = new CommandFire();
        AJ = new CommandJump();
        AR = new CommandRoll();
        AS = new CommandSkill();
    }

    Command GetCommand()
    {
        if(Input.GetKey("z"))
        {
            isPushUndoKey = true;
            if(stack.Count>0)
            {
                return stack.Pop();
            }
        }

        if (IsPressed(eBtn.left))
        {
            stack.Push(ML); return ML;
        }

        else if (IsPressed(eBtn.right))
        {
            stack.Push(MR); return MR;
        }

        else if (IsPressed(eBtn.up))
        {
            stack.Push(MU); return MU;
        }

        else if (IsPressed(eBtn.down))
        {
            stack.Push(MD); return MD;
        }
        else if (IsPressed(eBtn.jump))
        {
            return AJ;
        }

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


    void Update()
    {
        isPushUndoKey = false;
        Command command = GetCommand();

        if (command != null)
        {
            if (isPushUndoKey)
                command.Undo(actor);
            else
                command.Execute(actor);
        }
            
    }

}
