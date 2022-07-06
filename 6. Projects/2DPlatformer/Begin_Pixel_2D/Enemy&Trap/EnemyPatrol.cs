using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyPatrol : MonoBehaviour
{
    [Header("Patrol Points")]
    [SerializeField] private Transform leftEdge;
    [SerializeField] private Transform rightEdge;


    [Header("enemy")]
    [SerializeField] private Transform enemy;

    [Header("Movement Parameter")]
    [SerializeField] private float speed;
    private Vector3 initScale;
    private bool movingleft;

    [Header("Idle Behavior")]
    [SerializeField] private float idleDuration;
    private float idleTimer;

    [Header("enemy animator")]
    [SerializeField] private Animator anim;



    private void Awake()
    {
        initScale = enemy.localScale;
    }

    private void OnDisable()
    {
        anim.SetBool("Moving", false);
    }

    private void Update()
    {
        if (movingleft)
        {
            if (enemy.position.x >= leftEdge.position.x)
                MoveInDirection(-1);
            else
            {
                //change direction
                DirectionChange();
            }
        }

        else
        {
            if(enemy.position.x <= rightEdge.position.x)
                MoveInDirection(1);
            else
            {
                //change direction
                DirectionChange();
            }
        }
    }

    private void DirectionChange()
    {
        anim.SetBool("Moving", false);

        idleTimer += Time.deltaTime;

        if(idleTimer >= idleDuration)
            movingleft = !movingleft;
    }



    private void MoveInDirection(int _direction)
    {
        idleTimer = 0;
        anim.SetBool("Moving", true);

        //Make enemy face direction
        enemy.localScale = new Vector3(Mathf.Abs(initScale.x) * _direction * -1, initScale.y, initScale.z);

        //Move in direction
        enemy.position = new Vector3(enemy.position.x + Time.deltaTime * _direction * speed, enemy.position.y, enemy.position.z);
    }
}
