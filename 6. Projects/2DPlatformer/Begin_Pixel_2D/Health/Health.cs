using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    [SerializeField] private float startingHealth;
    public float currentHealth { get; private set;  } //get은 그 어떤 스크립트에서 해당 값을 받을 수 있다는 뜻이고, private set은 현재 스크립트에서만 set이 가능하다는 것.
    private Animator anim;
    private bool dead;


    private void Awake()
    {
        currentHealth = startingHealth;
        anim = GetComponent<Animator>();
    }

    public void TakeDamage(float _damage)
    {
        currentHealth = Mathf.Clamp(currentHealth - _damage, 0, startingHealth);   // value, min, max로 구성되어 있으며, value가 min 보다 작으면 min을 리턴 max보다 크면 max 리턴
        
        if(currentHealth > 0)
        {
            //player hurt
            anim.SetTrigger("hurt");
        }
        else
        {
            // player dead
            if (!dead)
            {
                anim.SetTrigger("die");
                GetComponent<PlayerMovement>().enabled = false;
                dead = true;
            }
        }


    }

    public void AddHealth(float _value)
    {
        currentHealth = Mathf.Clamp(currentHealth + _value, 0, startingHealth);   // value, min, max로 구성되어 있으며, value가 min 보다 작으면 min을 리턴 max보다 크면 max 리턴

    }

}
