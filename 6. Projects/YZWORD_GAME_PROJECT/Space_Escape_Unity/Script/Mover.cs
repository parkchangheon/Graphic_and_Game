using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mover : MonoBehaviour
{
    [SerializeField] float MoveSpeed = 10.0f;
    // Start is called before the first frame update
    void Start()
    {
        PrintInstructions();
    }

    // Update is called once per frame
    void Update()
    {
        MovePlayer();
    }

    void PrintInstructions()
    {
        Debug.Log("Welcome to the game");
        Debug.Log("Move your player with wasd or arrow keys");
        Debug.Log("Don't hit the walls!!");
    }

    void MovePlayer()
    {
        //델타 타입을 쓰게 되면, 느린컴퓨터와 빠른컴퓨터의 값차이를 없애는데 도움이 된다. 초당 10프레임에 0.1 값을 주면 1, 초당 100프레임에 0.01값을 주면 1이 되어 동일하다.
        float xValue = Input.GetAxis("Horizontal") * Time.deltaTime * MoveSpeed;
        float zValue = Input.GetAxis("Vertical") * Time.deltaTime * MoveSpeed;

        transform.Translate(xValue, 0, zValue);
    }

}
