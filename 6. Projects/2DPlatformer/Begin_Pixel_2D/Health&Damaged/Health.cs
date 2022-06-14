using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    [Header("Health")]
    [SerializeField] private float startingHealth;
    public float currentHealth { get; private set;  } //get은 그 어떤 스크립트에서 해당 값을 받을 수 있다는 뜻이고, private set은 현재 스크립트에서만 set이 가능하다는 것.
    private Animator anim;
    private bool dead;

    [Header("iFrames")]
    [SerializeField] private float iFrameDuration;
    [SerializeField] private int numberOfFlashes;
    private SpriteRenderer spriteRend;

    private void Awake()
    {
        currentHealth = startingHealth;
        anim = GetComponent<Animator>();
        spriteRend = GetComponent<SpriteRenderer>();
    }

    public void TakeDamage(float _damage)
    {
        currentHealth = Mathf.Clamp(currentHealth - _damage, 0, startingHealth);   // value, min, max로 구성되어 있으며, value가 min 보다 작으면 min을 리턴 max보다 크면 max 리턴
        
        if(currentHealth > 0)
        {
            //player hurt
            anim.SetTrigger("hurt");
            StartCoroutine(Invunerability());
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

    private IEnumerator Invunerability()
    {
        Physics2D.IgnoreLayerCollision(8, 9, true); // Layer 8,9는 서로 무시한다.
        //iVunerability duration
        for(int i=0; i<numberOfFlashes;i++)
        {
            spriteRend.color = new Color(1, 0, 0, 0.5f);  //피격시 색을 바꾸는 로직
            yield return new WaitForSeconds(iFrameDuration / (numberOfFlashes * 2));  //시간을 단축하는 로직
            spriteRend.color = Color.white;
            yield return new WaitForSeconds(iFrameDuration / (numberOfFlashes * 2));
        }
        Physics2D.IgnoreLayerCollision(8, 9, false);
    }
}
