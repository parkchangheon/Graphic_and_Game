using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HealthCollectible : MonoBehaviour
{
   [SerializeField] private float healthValue;
    private void OnTriggerEnter2D(Collider2D collision)
    {
        Debug.Log("the Heart Collapse");
        if(collision.tag == "Player"){
            collision.GetComponent<Health>().AddHealth(healthValue);
            gameObject.SetActive(false);
        }
    }
}
