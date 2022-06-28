using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpikeHead : Enemy_Damage
{
    [Header("SpikeHead Attributes")]
    [SerializeField] private float speed;
    [SerializeField] private float range;
    [SerializeField] private float checkDelay;
    [SerializeField] private LayerMask playerLayer;
    private bool attacking;
    private float checkTimer;
    private Vector3 destination;
    private Vector3[] directions = new Vector3[4];


    private void OnEnable()
    {
        Stop();
    }

    private void Update()
    {
        if(attacking) //move spike head to destination only is attacking
            transform.Translate(destination * Time.deltaTime * speed);
        else
        {
            checkTimer += Time.deltaTime;
            if (checkTimer > checkDelay)
                CheckForPlayer();
        }
    }


    private void CheckForPlayer()
    {
        CalculateDirections();

        //Check if Spikehead sees player all 4 direction
        for(int i = 0; i < directions.Length; i++)
        {
            Debug.DrawRay(transform.position, directions[i], Color.red);
            RaycastHit2D hit = Physics2D.Raycast(transform.position, directions[i], range, playerLayer);

            if(hit.collider != null && !attacking)
            {
                attacking = true;
                destination = directions[i];
                checkTimer = 0;
            }
        }
    }

    private void CalculateDirections()
    {
        directions[0] = transform.right * range; // Right Direction
        directions[1] = -transform.right * range; // Left Direction
        directions[2] = transform.up * range; // Up Direction
        directions[3] = -transform.up * range; // Down Direction
    }

    private void Stop()
    {
        destination = transform.position;
        attacking = false;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        base.OnTriggerEnter2D(collision);
        Stop(); //stop spikedhead once he hits something
    }

}


