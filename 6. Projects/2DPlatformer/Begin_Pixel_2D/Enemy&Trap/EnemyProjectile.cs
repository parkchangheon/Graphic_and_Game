using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyProjectile : Enemy_Damage
{
    [SerializeField] private float speed;
    [SerializeField] private float resetTime;
    private float lifetime;
    private Animator anim;
    private BoxCollider2D coll;

    private bool hit;

    private void Awake()
    {
        anim = GetComponent<Animator>();
        coll = GetComponent<BoxCollider2D>();
    }

    public void ActivateProjectile()
    {
        hit = false;
        lifetime = 0;
        gameObject.SetActive(true);
        coll.enabled = true;
    }

    private void Update()
    {
        if (hit) return;
        float movementSpeed = speed * Time.deltaTime;
        transform.Translate(-movementSpeed, 0, 0);

        lifetime += Time.deltaTime;
        if (lifetime > resetTime)
            gameObject.SetActive(false);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        hit = true;
        base.OnTriggerEnter2D(collision); // base 명령어는 부모 클래스로 들어갈 수 있도록 해주는 예약어이다. ==> 여기서는 부모클래스에서 정의한 ontriggerEnter2d를 위해 사용
        coll.enabled = false;

        if (anim != null)
            anim.SetTrigger("explode");
        else
            gameObject.SetActive(false);
    }
    private void Deactivate()
    {
        gameObject.SetActive(false);
    }
}
