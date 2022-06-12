using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    [SerializeField] private float startingHealth;
    private float currentHealth;

    private void Awake()
    {
        currentHealth = startingHealth;
    }

    public void TakeDamage(float _damage)
    {
        currentHealth = Mathf.Clamp(currentHealth - _damage, 0, startingHealth);   // value, min, max로 구성되어 있으며, value가 min 보다 작으면 min을 리턴 max보다 크면 max 리턴
        
        if(currentHealth > 0)
        {
            //player hurt
        }
        else
        {
            // player dead
        }


    }
}
